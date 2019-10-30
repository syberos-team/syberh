#ifndef UPLOAD_H
#define UPLOAD_H

#include "../../syberh-framework/src/framework/nativesdkhandlerbase.h"
#include "util/uploadmanager.h"

class TaskInfo{
public:
    // 任务ID
    QString uploadID;
    // 下载
    UploadManager *uploadManager;
};

class Upload : public NativeSdkHandlerBase
{
    Q_OBJECT

public:
    Q_INVOKABLE Upload();

    ~Upload();

    void request(QString callBackID,QString actionName,QVariantMap params);

    static int typeId;

    //下载状态
    enum ProgressStatus {
        Started = 1,
        Downloading = 2,
        Completed = 3
    };

private:
    // 上传
    void upload(QString callBackID, QString reqUrl, QString filePath);

    // 取消
    void cancel(QString callBackID, QString taskId);

    // 删除指针
    void deleteTask(QString taskId);

    qint64 m_bytesTotal;

    bool m_error;

public slots:

    // 开始上传
    void onStarted(QString callBackID);

    // 上传进度信息
    void onUploadProgress(QString callBackID, qint64 bytesReceived, qint64 bytesTotal);
    // 上传完成
    void onFinished(QString callBackID);
    // 下载过程中出现错误，关闭下载，并上报错误，这里未上报错误类型，可自己定义进行上报;
    void onError(QString callBackID, qint64 statusCode, QString error);
};

#endif // UPLOAD_H
