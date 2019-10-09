#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include "cstoragemanager.h"

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    //存储位置
    enum Storage {
        Internal = 1,   //内置
        Extended
    };

    explicit DownloadManager(QObject *parent = 0);
    ~DownloadManager();

    // 设置是否支持断点续传
    void setDownInto(bool isSupportBreakPoint);
    // 获取当前下载链接
    QString getDownloadUrl();
    // 开始下载文件，传入下载链接和文件的路径
    void downloadFile(QString url , QString fileName);
    // 停止下载工作
    void stopWork();
    // 暂停下载按钮被按下,暂停当前下载
    void stopDownload();
    // 重置参数
    void reset();
    // 删除文件
    void removeFile(QString fileName);
    // 停止下载按钮被按下，关闭下载，重置参数，并删除下载的临时文件
    void closeDownload();

    //设置downloadId
    void setDownloadId(QString downloadId);
    //设置存储位置
    void setStorage(DownloadManager::Storage storage);

    DownloadManager::Storage getStorage();

    QString getDownloadId();

    QString getMPath();

    qint64 getBytesReceived();

    qint64 getBytesTotal();

    QString getDownloadFileSuffix();

private:
    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_reply;
    QUrl m_url;
    QString m_fileName;
    QString m_path;
    bool m_isSupportBreakPoint;
    qint64 m_bytesReceived;
    qint64 m_bytesTotal;
    qint64 m_bytesCurrentReceived;
    bool m_isStop;
    QString m_downloadId;
    Storage m_storage;  //存储位置
    qint64 m_storageFreeSize;   //存储空间剩余
    CStorageManager *m_storageManager;
    QString m_tmpFileSuffix;       //下载时的临时文件后缀
    //获取下载文件的大小
    qint64 downloadFileSize();
    //获取存储空间剩余
    qint64 storageFreeSize();

signals:

    void signalStarted(QString downloadId, QString path);

    void signalDownloadProcess(QString downloadId, QString path, qint64 bytesReceived, qint64 bytesTotal);

    void signalReplyFinished(QString downloadId, QString path, int statusCode, QString error);

    void signalDownloadError(QString downloadId, qint64 statusCode, QString error);

public slots:
    // 下载进度信息
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    // 获取下载内容，保存到文件中
    void onReadyRead();
    // 下载完成
    void onFinished();
    // 下载过程中出现错误，关闭下载，并上报错误，这里未上报错误类型，可自己定义进行上报;
    void onError(QNetworkReply::NetworkError code);
};

#endif // DOWNLOADMANAGER_H
