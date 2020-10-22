#include "upload.h"
#include "framework/common/errorinfo.h"
#include "util/validator.h"
#include <QJsonObject>
#include <QDebug>

using namespace NativeSdk;

//key 既是downloadID也是callbackID
static QMap<QString, TaskInfo*> tasks;

Upload::Upload()
{
    m_error = false;
}

QJsonObject successJson(QString callbackId, int status, qint64 received, qint64 total){
    QJsonObject json;
    json.insert("uploadID", callbackId);
    json.insert("status", status);
    json.insert("received", received);
    json.insert("total", total);
    return json;
}

void Upload::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    if (actionName == "start") {
        start(callbackID, params);
    } else if (actionName == "cancel") {
        cancel(callbackID, params);
    }
}

void Upload::start(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "params" << params;
    globalCallbackID = callbackID.toLong();

    QString reqUrl = params.value("url").toString();
    QString filePath = params.value("filePath").toString();
    QString name = params.value("name").toString();

    if (name == "") {
        qDebug() << "name parameter is not empty" << reqUrl << endl;
        signalManager()->failed(globalCallbackID, ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "name不能为空"));
        globalCallbackID = 0;
        return;
    }

    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << Q_FUNC_INFO << "文件地址不存在：" << filePath << endl;
        signalManager()->failed(globalCallbackID, ErrorInfo::FileNotExists, "文件不存在");
        globalCallbackID = 0;
        return;
    }

    // 检查网络
    if (!Validator::netWorkConnected()) {
        signalManager()->failed(globalCallbackID, ErrorInfo::NetworkError, ErrorInfo::message(ErrorInfo::NetworkError, "请检查网络状态"));
        globalCallbackID = 0;
        return;
    }

    //检查url
    if(!Validator::isHttpUrl(reqUrl)){
        qDebug() << "url parameter is not starts with http or https: " << reqUrl << endl;
        signalManager()->failed(globalCallbackID, ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "URL无效"));
        globalCallbackID = 0;
        return;
    }

    UploadManager *uploadManager = new UploadManager();

    connect(uploadManager, SIGNAL(signalUploadProcess(QString, qint64, qint64)), this, SLOT(onUploadProgress(QString, qint64, qint64)));
    connect(uploadManager, SIGNAL(signalReplyFinished(QString)), this, SLOT(onFinished(QString)));
    connect(uploadManager, SIGNAL(signalError(QString, qint64, QString)), this, SLOT(onError(QString, qint64, QString)));
    connect(uploadManager, SIGNAL(signalStarted(QString)), this, SLOT(onStarted(QString)));
    uploadManager->setUploadId(callbackID);
    uploadManager->uploadFile(params);


    // 当前任务记录到tasks
    TaskInfo *taskInfo = new TaskInfo();
    taskInfo->uploadID = callbackID;
    taskInfo->uploadManager = uploadManager;
    tasks.insert(callbackID, taskInfo);
}


void Upload::cancel(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "params" << params;
    globalCallbackID = callbackID.toLong();

    QString taskId = params.value("taskId").toString();
    TaskInfo *taskInfo = tasks.value(taskId);
    if (taskInfo != NULL) {
        taskInfo->uploadManager->stopWork();
        deleteTask(taskId);

        QJsonObject json;
        json.insert("result", true);
        signalManager()->success(globalCallbackID, json);
    } else {
        signalManager()->failed(globalCallbackID, ErrorInfo::CannelFailed, ErrorInfo::message(ErrorInfo::CannelFailed, "任务不存在或已完成"));
    }
}

void Upload::deleteTask(QString taskId)
{
    qDebug() << Q_FUNC_INFO << "taskId" << taskId;
    TaskInfo *taskInfo = tasks.value(taskId);
    if (taskInfo!=NULL) {

        delete taskInfo->uploadManager;
        taskInfo->uploadManager = NULL;

        delete taskInfo;
        taskInfo = NULL;
        tasks.remove(taskId);

    }
}

void Upload::onUploadProgress(QString callbackID, qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << Q_FUNC_INFO << "！！！！！-----------上传文件，onUploadProgress." << endl;

    // 由于发送error信号后，程序还会执行此信号 所以做一下判断拦截
    if (m_error) {
        return;
    }

    // 上传完成后，上传大小和总大小程序重置为0了，所以如果总大小为0，就判断拦截
    if (bytesTotal == 0) {
        return;
    }

    QJsonObject json = successJson(callbackID, Downloading, bytesReceived, bytesTotal);

    m_bytesTotal = bytesTotal;

//    qDebug() << Q_FUNC_INFO << "！！！！！-----------上传文件，已上传：" + QString::number(bytesReceived) + "总大小：" + QString::number(bytesTotal) << endl;

    signalManager()->success(globalCallbackID, json);
}
void Upload::onFinished(QString callbackID)
{

    qDebug() << Q_FUNC_INFO << "！！！！！-----------上传文件，onFinished." << endl;

    // 由于发送error信号后，程序还会执行此信号 所以做一下判断拦截
    if (m_error) {
        return;
    }
    // 任务完成，删除任务
    deleteTask(callbackID);

//    qDebug() << Q_FUNC_INFO << "！！！！！-----------上传文件，完成." << endl;

    QJsonObject json = successJson(callbackID, Completed, m_bytesTotal, m_bytesTotal);
    signalManager()->success(globalCallbackID, json);
}

void Upload::onError(QString callbackID, qint64 statusCode, QString error)
{
    // 任务异常，删除任务
    deleteTask(callbackID);
    m_error = true;
    signalManager()->failed(globalCallbackID, statusCode, error);
}

void Upload::onStarted(QString callbackID)
{
    QJsonObject json = successJson(callbackID, Started, 0, 0);
    signalManager()->success(globalCallbackID, json);
}


