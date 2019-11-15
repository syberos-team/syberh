#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H

#include "../../syberh-framework/src/framework/nativesdkhandlerbase.h"
#include <QtNetwork>
#include <QObject>
#include "./util/downloadmanager.h"

class TaskInfo{
public:
    // 任务ID
    QString downloadID;
    // 下载
    DownloadManager *downloadManager;
};

#define STORAGE_INTERNAL "internal"
#define STORAGE_EXTENDED "extended"


class Download : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    //下载状态
    enum ProgressStatus {
        Started = 1,
        Downloading = 2,
        Completed = 3
    };

    Q_INVOKABLE Download();
    ~Download();

    void request(QString callBackID,QString actionName,QVariantMap params);
    void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

private :
    void start(QString callbackId, QString url, QString name, QString storage);

    void cancel(QString callbackId, QString downloadID);

    TaskInfo* findTaskInfo(DownloadManager *downloadManager);
    //删除TaksInfo对象，断开连接的信号，并移除任务
    void removeTask(QString downloadId);

public slots:

    // 开始下载
    void onStarted(QString downloadId, QString path);

    void onDownloadProcess(QString downloadId, QString path, qint64 received, qint64 total);

    void onReplyFinished(QString downloadId, QString path, int statusCode, QString errorMessage);

    void onDownloadError(QString downloadId, qint64 statusCode, QString error);
};


#endif // DOWNLOADFILE_H
