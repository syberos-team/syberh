#include "download.h"
#include "helper.h"

#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QDir>
#include <QObject>
#include <QDebug>

//key 既是downloadID也是callbackId
static QMap<QString, TaskInfo*> tasks;


QString getDownloadPath(){
    Helper *helper = Helper::instance();
    QString sopid = helper->sopid();

    QString downloadPath = helper->getInnerStorageRootPath() + "/" + sopid;
    if(!helper->exists(downloadPath)){
        QDir dir(downloadPath);
        dir.mkpath(downloadPath);
    }
    return downloadPath;
}

QJsonObject successJson(QString callbackId, QString path, int status, qint64 received, qint64 total){
    QJsonObject json;
    json.insert("downloadID", callbackId);
    json.insert("path", path);
    json.insert("status", status);
    json.insert("received", received);
    json.insert("total", total);
    return json;
}


int Download::typeId = qRegisterMetaType<Download *>();

Download::Download()
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
}

Download::~Download()
{
    delete manager;
    manager = NULL;
}



void Download::request(QString callbackId, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "callbackId" << callbackId << "actionName" << actionName << "params" << params << endl;

    if (actionName == "start") {
        start(callbackId, params.value("url").toString(), params.value("name").toString());
    } else if (actionName == "cancel"){
        cancel(params.value("downloadID").toString());
    } else {
        emit failed(callbackId.toLong(), 500, "Invalid call");
    }
}

void Download::submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes){
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
}

void Download::start(QString callbackId, QString url, QString name){
    if (name.isEmpty()) {
        name = callbackId;
    }
    qDebug() << Q_FUNC_INFO << "url:" << url << "name:" << name << endl;

    QUrl qurl(url);
    QNetworkRequest request(qurl);

    QString urlAddr = url.toLower();
    if(urlAddr.startsWith("https")){
        QSslConfiguration config;
        config.setPeerVerifyMode(QSslSocket::VerifyNone);
        config.setProtocol(QSsl::UnknownProtocol);
        request.setSslConfiguration(config);
    }

    QNetworkReply *reply = manager->get(request);

    TaskInfo *taskInfo = new TaskInfo();
    taskInfo->downloadID = callbackId;
    taskInfo->reply = reply;
    taskInfo->name = name;
    taskInfo->path = getDownloadPath() + "/" + name;
    taskInfo->cancel = false;
    taskInfo->canCancel = true;

    tasks.insert(callbackId, taskInfo);

    QJsonObject json = successJson(callbackId, taskInfo->path, Started, 0, 0);
    emit success(callbackId.toLong(), json);
}

void Download::cancel(QString downloadID){
    if (downloadID == "") {
        emit failed(downloadID.toLong(), 500, "downloadID为空");
        return;
    }
    if (!tasks.contains(downloadID)) {
        emit failed(downloadID.toLong(), 500, "下载任务不存在或已完成");
        return;
    }
    TaskInfo *taskInfo = tasks.value(downloadID);
    taskInfo->cancel = true;

    QJsonObject json;
    json.insert("result", true);
    emit success(taskInfo->downloadID.toLong(), json);
}


void Download::finished(QNetworkReply *reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    qDebug() << Q_FUNC_INFO << " statusCode: " << statusCode.toString() << " error: " << reply->error() << endl;

    TaskInfo *taskInfo = findTaskInfoByReply(reply);
    if(taskInfo==NULL){
        qDebug() << Q_FUNC_INFO << "TaskInfo not found, QNetworkReply:" << reply << reply->url() << endl;
        reply->deleteLater();
        return;
    }

    if(downloadCannel(taskInfo, true)){
        reply->deleteLater();
        return;
    }

    QString path = taskInfo->path;
    QString callbackId = taskInfo->downloadID;

    if(QNetworkReply::NoError == reply->error()) {
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly)){
            qDebug() << Q_FUNC_INFO << " save fail: " << file.error() << file.errorString() << endl;
            reply->deleteLater();
            emit failed(callbackId.toLong(), 500, file.errorString());
            return;
        }

        qDebug() << "!!!!!!!! begin" << path << reply->url() << endl;

        if(downloadCannel(taskInfo, true)){
            if(file.exists()){
                file.close();
                file.remove();
            }
            reply->deleteLater();
            return;
        }

        qint64 bytesTotal = reply->size();
        qint64 bytesReceived = 0;

        qint64 maxlen = 1024;
        while(!reply->atEnd()){
            if(downloadCannel(taskInfo, true)){
                if(file.exists()){
                    file.close();
                    file.remove();
                }
                reply->deleteLater();
                return;
            }
            QByteArray data = reply->read(maxlen);
            file.write(data.data(), data.length());

            bytesReceived += data.length();
            downloadProgress(callbackId, path, bytesReceived, bytesTotal);
        }
        qDebug() << "!!!!!!!! read end" << endl;
        file.close();

        tasks.remove(callbackId);
        delete taskInfo;
        reply->deleteLater();

        QJsonObject json = successJson(callbackId, path, Completed, bytesReceived, bytesTotal);

        qDebug() << "!!!!!!!! success" << json << endl;
        emit success(callbackId.toLong(), json);
    }else{
        long errorCode = reply->error();
        QString errorMessage = reply->errorString();
        reply->deleteLater();
        emit failed(callbackId.toLong(), errorCode, errorMessage);
    }
}


void Download::downloadProgress(QString callbackId, QString path, qint64 bytesReceived, qint64 bytesTotal){
    QJsonObject json = successJson(callbackId, path, Downloading, bytesReceived, bytesTotal);
    qDebug() << "!!!!!!!! downloadProgress" << json << endl;
    emit success(callbackId.toLong(), json);
}

TaskInfo* Download::findTaskInfoByReply(QNetworkReply *reply){
    QMap<QString, TaskInfo*>::ConstIterator it = tasks.begin();
    for(; it!=tasks.end(); it++){
        TaskInfo *taskInfo = it.value();
        if(taskInfo->reply == reply){
            return taskInfo;
        }
    }
    return NULL;
}

bool Download::downloadCannel(TaskInfo* taskInfo, bool emitFailed){
    if(taskInfo->canCancel && taskInfo->cancel){
        if(emitFailed){
            emit failed(taskInfo->downloadID.toLong(), 200, "下载取消");
        }
        return true;
    }
    return false;
}
