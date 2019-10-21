#include "upload.h"
#include "util/uploadmanager.h"
#include <QJsonObject>
#include <QDebug>
#include "../../syberh-framework/src/util/validator.h"

int Upload::typeId = qRegisterMetaType<Upload *>();

//key 既是downloadID也是callbackId
static QMap<QString, TaskInfo*> tasks;

Upload::Upload()
{
    m_error = false;
}
Upload::~Upload()
{}
QJsonObject successJson(QString callbackId, int status, qint64 received, qint64 total){
    QJsonObject json;
    json.insert("uploadID", callbackId);
    json.insert("status", status);
    json.insert("received", received);
    json.insert("total", total);
    return json;
}
void Upload::request(QString callBackID, QString actionName, QVariantMap params)
{
    qDebug() << "callbackId:" << callBackID << "actionName:" << actionName << "params:" << params << endl;

    if (actionName == "start") {
        upload(callBackID, params.value("url").toString(), params.value("filePath").toString());
    } else if (actionName == "cancel") {
        cancel(callBackID, params.value("uploadID").toString());
    }
}
void Upload::upload(QString callBackID, QString reqUrl, QString filePath)
{
    // 检查网络
    if (!netWorkConnected()) {
        emit failed(callBackID.toLong(), ErrorInfo::NetworkError, ErrorInfo::message(ErrorInfo::NetworkError, "请检查网络状态"));
        return;
    }

    //检查url
    if(!Validator::isHttpUrl(reqUrl)){
        qDebug() << "url parameter is not starts with http or https: " << reqUrl << endl;
        emit failed(callBackID.toLong(), ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "URL无效"));
        return;
    }

    UploadManager *uploadManager = new UploadManager();


    connect(uploadManager, SIGNAL(signalUploadProcess(QString, qint64, qint64)), this, SLOT(onUploadProgress(QString, qint64, qint64)));
    connect(uploadManager, SIGNAL(signalReplyFinished(QString)), this, SLOT(onFinished(QString)));
    connect(uploadManager, SIGNAL(signalError(QString, qint64, QString)), this, SLOT(onError(QString, qint64, QString)));
    connect(uploadManager, SIGNAL(signalStarted(QString)), this, SLOT(onStarted(QString)));
    uploadManager->setUploadId(callBackID);
    uploadManager->uploadFile(reqUrl, filePath);


    // 当前任务记录到tasks
    TaskInfo *taskInfo = new TaskInfo();
    taskInfo->uploadID = callBackID;
    taskInfo->uploadManager = uploadManager;
    tasks.insert(callBackID, taskInfo);



}

void Upload::cancel(QString callBackID, QString taskId)
{
    TaskInfo *taskInfo = tasks.value(taskId);
    if (taskInfo != NULL) {
        taskInfo->uploadManager->stopWork();
        deleteTask(taskId);

        QJsonObject json;
        json.insert("result", true);
        emit success(callBackID.toLong(), json);
    } else {
        emit failed(callBackID.toLong(), ErrorInfo::CannelFailed, ErrorInfo::message(ErrorInfo::CannelFailed, "任务不存在或已完成"));
    }
}

void Upload::deleteTask(QString taskId)
{
    TaskInfo *taskInfo = tasks.value(taskId);
    if (taskInfo!=NULL) {

        delete taskInfo->uploadManager;
        taskInfo->uploadManager = NULL;

        delete taskInfo;
        taskInfo = NULL;
        tasks.remove(taskId);

    }
}

void Upload::onUploadProgress(QString callBackID, qint64 bytesReceived, qint64 bytesTotal)
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

    QJsonObject json = successJson(callBackID, Downloading, bytesReceived, bytesTotal);

    m_bytesTotal = bytesTotal;

//    qDebug() << Q_FUNC_INFO << "！！！！！-----------上传文件，已上传：" + QString::number(bytesReceived) + "总大小：" + QString::number(bytesTotal) << endl;

    emit success(callBackID.toLong(), json);
}
void Upload::onFinished(QString callBackID)
{

    qDebug() << Q_FUNC_INFO << "！！！！！-----------上传文件，onFinished." << endl;

    // 由于发送error信号后，程序还会执行此信号 所以做一下判断拦截
    if (m_error) {
        return;
    }
    // 任务完成，删除任务
    deleteTask(callBackID);

//    qDebug() << Q_FUNC_INFO << "！！！！！-----------上传文件，完成." << endl;

    QJsonObject json = successJson(callBackID, Completed, m_bytesTotal, m_bytesTotal);
    emit success(callBackID.toLong(), json);
}

void Upload::onError(QString callBackID, qint64 statusCode, QString error)
{
    // 任务异常，删除任务
    deleteTask(callBackID);
    m_error = true;
    emit failed(callBackID.toLong(), statusCode, error);
}

void Upload::onStarted(QString callBackID)
{
    QJsonObject json = successJson(callBackID, Started, 0, 0);
    emit success(callBackID.toLong(), json);
}


