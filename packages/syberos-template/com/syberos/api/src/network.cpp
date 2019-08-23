#include "network.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QJsonObject>

int NetWork::typeId = qRegisterMetaType<NetWork *>();

NetWork::NetWork()
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finished(QNetworkReply*)));
}
NetWork::~NetWork()
{
    delete manager;
}
void NetWork::request(QString callBackID, QString actionName, QVariantMap params)
{

    // 检查网络
    if (!netWorkConnected()) {
        emit failed(callBackID.toLong(),NETWORK_ERROR,ErrorInfo::m_errorCode.value(NETWORK_ERROR));
        return;
    }

    qDebug() << Q_FUNC_INFO << "NetWork callbackID is" << callBackID << "actionName is" << actionName << "params is" << params << endl;

    QString url = params.value("url").toString();
    QString method = params.value("method").toString();
    if (method == "") {
        qDebug() << Q_FUNC_INFO << "params type is null, set default values: get callbackID is " << callBackID << endl;
        method = "get";
    }

    QString dataType = params.value("dataType").toString();
    if (dataType == "") {
        dataType = "json";
    }

    if (dataType.toLower() != "json"
            && dataType.toLower() != "text") {
        emit failed(callBackID.toLong(), 500, "Invalid dataType param");
        return;
    }

    QNetworkRequest request;

    QString urlAddr = url.toLower();
    if(urlAddr.startsWith("https")){
        QSslConfiguration config;
        config.setPeerVerifyMode(QSslSocket::VerifyNone);
        config.setProtocol(QSsl::UnknownProtocol);
        request.setSslConfiguration(config);
    }

    QVariantMap headers = params.value("headers").toMap();

    qDebug() << Q_FUNC_INFO << "headers is " << headers  <<endl;

    QVariantMap::Iterator headerIt = headers.begin();
    while (headerIt != headers.end()) {
        request.setRawHeader(headerIt.key().toUtf8(), headerIt.value().toString().toUtf8());
        headerIt++;
    }
    if (!headers.contains("Content-Type")){
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    }

    request.setUrl(url);

    QNetworkReply *reply;

    if ("get" == method.toLower()) {
        reply = manager->get(request);
    } else if ("post" == method.toLower()) {
        QVariantMap data = params.value("data").toMap();
        QVariantMap::Iterator it = data.begin();
        QString content;
        while (it != data.end()) {
            content.append(it.key()).append("=").append(it.value().toString());
            it++;
            if (it != data.end()) {
                content.append("&");
            }
        }
        reply = manager->post(request, content.toUtf8());
    } else if ("put" == method.toLower()) {
        QVariantMap data = params.value("data").toMap();
        QVariantMap::Iterator it = data.begin();
        QString content;
        while (it != data.end()) {
            content.append(it.key()).append("=").append(it.value().toString());
            it++;
            if (it != data.end()) {
                content.append("&");
            }
        }
        reply = manager->put(request, content.toUtf8());
    } else if ("delete" == method.toLower()) {
        reply = manager->deleteResource(request);
    } else {
        emit failed(callBackID.toLong(), 500, "Invalid type param");
        return;
    }

    TaskInfo *taskInfo = new TaskInfo();
    taskInfo->dataType = dataType;
    taskInfo->reply = reply;

    tasks[callBackID] = taskInfo;

}


void NetWork::finished(QNetworkReply *reply)
{
    qDebug() << Q_FUNC_INFO << endl;

    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    qDebug() << Q_FUNC_INFO << " statusCode: " << statusCode.toString() << " error: " << reply->error() << endl;

    QString result = QString(reply->readAll());

    qDebug() << Q_FUNC_INFO << " result: " << result << " url:" << reply->url().url() <<endl;

    QString callBackId;
    QString datatype;

    QMap<QString, TaskInfo*>::Iterator it = tasks.begin();
    while(it != tasks.end()){
        TaskInfo *taskInfo = it.value();
        if (taskInfo->reply == reply) {
            callBackId = it.key();
            datatype = taskInfo->dataType;
            tasks.remove(it.key());
            delete taskInfo;
            taskInfo = NULL;
            break;
        }
        it++;
    }
//    qDebug() << Q_FUNC_INFO << " tasks.size(): " << tasks.size() <<endl;
//    qDebug() << Q_FUNC_INFO << " callBackId: " << callBackId <<endl;

    if(QNetworkReply::NoError == reply->error()) {
        if (datatype.toLower() == "json") {
            QJsonObject json;
            json.insert("data", result);
            emit success(callBackId.toLong(), json);
        } else {
            emit success(callBackId.toLong(), result);
        }
    }else{
        qDebug() << Q_FUNC_INFO << " result error " <<endl;
        emit failed(callBackId.toLong(), 500, reply->errorString());
    }

    reply->deleteLater();

}
