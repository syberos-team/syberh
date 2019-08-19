#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H

#include "../framework/nativesdkhandlerbase.h"
#include <QtNetwork>
#include <QObject>

class TaskInfo{
public:
    // 任务ID
    QString downloadID;
    // 下载文件名
    QString name;
    // 下载文件本地路径
    QString path;

    QNetworkReply* reply;
    // 已取消
    bool cancel;
    // 是否能取消
    bool canCancel;
};


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

    void downloadProgress(QString callbackId, QString path, qint64 bytesReceived, qint64 bytesTotal);

private :
    void start(QString callbackId, QString url, QString name);

    void cancel(QString downloadID);

    QNetworkAccessManager *manager;

    TaskInfo* findTaskInfoByReply(QNetworkReply *reply);
    bool downloadCannel(TaskInfo* taskInfo, bool emitFailed = false);

public slots:
    void finished(QNetworkReply *reply);
};


#endif // DOWNLOADFILE_H
