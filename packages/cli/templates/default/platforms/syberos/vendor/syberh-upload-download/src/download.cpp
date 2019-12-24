#include "download.h"
#include "../../syberh-framework/src/helper.h"

#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QDir>
#include <QObject>
#include <QDebug>
#include <QFile>
#include "../../syberh-framework/src/framework/common/errorinfo.h"
#include "../../syberh-framework/src/util/validator.h"

//key 既是downloadID也是callbackId
static QMap<QString, TaskInfo*> tasks;
// 防止并发，文件名重复导致数据写入到同一个文件内 先缓存文件名(文件路径) key 文件名(文件路径) val 文件名(文件路径)
static QMap<QString, QString> fileNames;


QString getDownloadPath(DownloadManager::Storage storage){
    Helper *helper = Helper::instance();
    QString sopid = helper->sopid();

    QString basePath = helper->getInnerStorageRootPath();
    if(storage==DownloadManager::Extended){
        basePath = helper->getExternStorageRootPath();
    }

    QString downloadPath = basePath + "/" + sopid;
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
    process = new QProcess();
    isnetWork = true;
}

Download::~Download() {
    delete process;
    QMap<QString, TaskInfo*>::ConstIterator it = tasks.begin();
    for(; it!=tasks.end(); it++){
        removeTask(it.key());
    }
    tasks.clear();
    fileNames.clear();
}



void Download::request(QString callbackId, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "callbackId" << callbackId << "actionName" << actionName << "params" << params << endl;

    if (actionName == "start") {
        start(callbackId, params.value("url").toString(), params.value("name").toString(), params.value("storage").toString());
    } else if (actionName == "cancel"){
        cancel(callbackId, params.value("downloadID").toString());
    } else {
        emit failed(callbackId.toLong(), ErrorInfo::InvalidCall, ErrorInfo::message(ErrorInfo::InvalidCall, "方法不存在"));
    }
}

void Download::submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes){
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
}

void Download::start(QString callbackId, QString url, QString name, QString storage){
    // 检查网络
    if (!netWorkConnected()) {
        emit failed(callbackId.toLong(), ErrorInfo::NetworkError, ErrorInfo::message(ErrorInfo::NetworkError, "请检查网络状态"));
        return;
    }

    // if(isnetWork){
    //     // 检查网络是否可用
    //     QString network_cmd = "ping 114.114.114.114 -w 1";//向www.baidu.com请求两包数据，每包数据超时时间为1s
    //     QString result;
    //     process->start(network_cmd);   //调用ping 指令
    //     process->waitForFinished();    //等待指令执行完毕
    //     result = process->readAll();   //获取指令执行结果
    //     qDebug() << Q_FUNC_INFO << "result" << result << endl;
    //     if(!result.contains(QString("ttl="))){   //若包含TTL=字符串则认为网络在线
    //         qDebug() << Q_FUNC_INFO << "process:false"  << endl;
    //         emit failed(callbackId.toLong(), ErrorInfo::NetworkError, ErrorInfo::message(ErrorInfo::NetworkError, "请检查网络是否可用"));
    //         return;
    //     }
    //     isnetWork = false;
    // }

    if (name.isEmpty()) {
        name = callbackId;
    }
    qDebug() << Q_FUNC_INFO << "url:" << url << "name:" << name << endl;

    //检查url
    if(!Validator::isHttpUrl(url)){
        qDebug() << "url parameter is not starts with http or https: " << url << endl;
        emit failed(callbackId.toLong(), ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "URL无效"));
        return;
    }

    DownloadManager *downloadManager = new DownloadManager(this);
    //设置下载ID
    downloadManager->setDownloadId(callbackId);
    //设置存储位置
    storage = storage.toLower();
    if(storage==STORAGE_INTERNAL){
        downloadManager->setStorage(DownloadManager::Internal);
    }else if(storage==STORAGE_EXTENDED){
        downloadManager->setStorage(DownloadManager::Extended);
    }

    connect(downloadManager, &DownloadManager::signalStarted, this, &Download::onStarted);
    connect(downloadManager, &DownloadManager::signalDownloadProcess, this, &Download::onDownloadProcess);
    connect(downloadManager, &DownloadManager::signalReplyFinished, this, &Download::onReplyFinished);
    connect(downloadManager, &DownloadManager::signalDownloadError, this, &Download::onDownloadError);


    TaskInfo *taskInfo = new TaskInfo();
    taskInfo->downloadID = callbackId;
    taskInfo->downloadManager = downloadManager;
    tasks.insert(callbackId, taskInfo);

    QString basePath = getDownloadPath(downloadManager->getStorage());
    QString path = basePath + "/" + name;

    // 判断当前文件是否重复，如果重复名称添加序号
    QStringList nameSplit = name.split(".");
    int i = 1;
    while (QFile::exists(path)
           || QFile::exists(path + downloadManager->getDownloadFileSuffix())
           || fileNames.value(path) != NULL) {
        if (nameSplit.size() == 2) {
            // 文件名只有一个小数点的情况
            path = basePath + "/" + nameSplit[nameSplit.size() - 2] + "(" + QString::number(i) + ")." + nameSplit[nameSplit.size() - 1];
        } else if (nameSplit.size() > 2) {
            // 文件名出现多个小数点的情况，nameSplit.size()-2 是数组倒数第2项

            qDebug() << "lastName 倒数第2项的名字: " << nameSplit[nameSplit.size()-2] << endl;

            QString lastName = nameSplit[nameSplit.size()-2].section('(', 0);

            qDebug() << "lastName 倒数第2项的名字--去掉括号后: " << lastName << endl;

            nameSplit.replace(nameSplit.size()-2, lastName + "(" + QString::number(i) + ")");
            path = basePath + "/" + nameSplit.join('.');
        } else {
            // 文件名没有小数点的情况
            path = basePath + "/" + nameSplit[nameSplit.size() - 1] + "(" + QString::number(i) + ")";
        }
        i++;
    }
    // add缓存文件路径
    fileNames.insert(path, path);

    downloadManager->downloadFile(url, path);

}

void Download::cancel(QString callbackId, QString downloadID){
    if (downloadID == "") {
        emit failed(callbackId.toLong(), ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "downloadID为空"));
        return;
    }
    if (!tasks.contains(downloadID)) {
        emit failed(callbackId.toLong(), ErrorInfo::CannelFailed, ErrorInfo::message(ErrorInfo::CannelFailed, "任务不存在或已完成"));
        return;
    }
    TaskInfo *taskInfo = tasks.value(downloadID);

    // 删除缓存文件路径
    fileNames.remove(taskInfo->downloadManager->getMPath());

    taskInfo->downloadManager->closeDownload();

    QJsonObject json;
    json.insert("result", true);
    emit success(callbackId.toLong(), json);
}


TaskInfo* Download::findTaskInfo(DownloadManager *downloadManager){
    QMap<QString, TaskInfo*>::ConstIterator it = tasks.begin();
    for(; it!=tasks.end(); it++){
        TaskInfo *taskInfo = it.value();
        if(taskInfo->downloadManager == downloadManager){
            return taskInfo;
        }
    }
    return NULL;
}

void Download::removeTask(QString downloadId){
    qDebug() << Q_FUNC_INFO << "download removeTask " << endl;
    if(tasks.contains(downloadId)){
        TaskInfo *taskInfo = tasks.value(downloadId);
        if(taskInfo!=NULL){
            disconnect(taskInfo->downloadManager, &DownloadManager::signalDownloadProcess, this, &Download::onDownloadProcess);
            disconnect(taskInfo->downloadManager, &DownloadManager::signalReplyFinished, this, &Download::onReplyFinished);
            disconnect(taskInfo->downloadManager, &DownloadManager::signalDownloadError, this, &Download::onDownloadError);
            tasks.remove(downloadId);

            taskInfo->downloadManager->deleteLater();
            taskInfo->downloadManager = NULL;

            delete taskInfo;
            taskInfo = NULL;
        }
    }
}


// 更新下载进度;
void Download::onDownloadProcess(QString downloadId, QString path, qint64 bytesReceived, qint64 bytesTotal) {
    QJsonObject json = successJson(downloadId, path, Downloading, bytesReceived, bytesTotal);
//    qDebug() << Q_FUNC_INFO << "downloadProgress" << json << endl;
    emit success(downloadId.toLong(), json);
}


void Download::onReplyFinished(QString downloadId, QString path, int statusCode, QString errorMessage){
    qDebug() << Q_FUNC_INFO << "download finished " << statusCode << errorMessage << endl;

    qint64 received = 0;
    qint64 total = 0;
    TaskInfo *taskInfo = tasks.value(downloadId);
    if(taskInfo!=NULL){
        received = taskInfo->downloadManager->getBytesReceived();
        total = taskInfo->downloadManager->getBytesTotal();
    }

    // 删除缓存文件路径
    fileNames.remove(taskInfo->downloadManager->getMPath());

    // 根据状态码判断当前下载是否出错, 大于等于400算错误
    if (statusCode >= 400) {
        qDebug() << Q_FUNC_INFO << "download failed " << statusCode << errorMessage << endl;
        emit failed(downloadId.toLong(), ErrorInfo::NetworkError, ErrorInfo::message(ErrorInfo::NetworkError, errorMessage));
    }
    else {
        QJsonObject json = successJson(downloadId, path, Completed, received, total);

        qDebug() << Q_FUNC_INFO << "download success " << statusCode << errorMessage << endl;
        emit success(downloadId.toLong(), json);
    }
    removeTask(downloadId);
}

void Download::onDownloadError(QString downloadId, qint64 code, QString error){
    qDebug() << Q_FUNC_INFO << "download failed " << code << error << endl;
    emit failed(downloadId.toLong(), code, error);
    removeTask(downloadId);
}
void Download::onStarted(QString downloadId, QString path)
{
    QJsonObject json = successJson(downloadId, path, Started, 0, 0);
    emit success(downloadId.toLong(), json);
}
