#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QtNetwork>

class FileInfo {
public:
    QString filename;
    QString abstractPath;
};


class DownloadTask{
public:
    long downloadID;
    QString url;
    QString name;
    QNetworkReply* reply;
};

class Download : public QObject
{
    Q_OBJECT
public:

    explicit Download(QObject *parent = 0);

    static Download* instance();

    QString getDownloadDir();

    /**
     * @brief cancel 取消下载
     * @param downloadID 要取消下载的任务Id
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    Q_INVOKABLE long cancel(long downloadID);
    /**
     * @brief getFileInfos 获取所有下载文件信息
     * @return 成功则返回FileInfo数组。
              失败则返回错误码。
     */
    Q_INVOKABLE QList<FileInfo> getFileInfos();
    /**
     * @brief pause 暂停下载 (暂不支持)
     * @param downloadID 要暂停的下载任务Id
     * @return 成功则无返回。
                      失败则返回错误码。
     */
    Q_INVOKABLE long pause(long downloadID);
    /**
     * @brief removeFileInfos 移除下载文件记录。
     * @param downloadIDs 整型数组, 要移除下载文件的Id。
     * @return 成功则无返回。
                      失败则返回错误码。
     */
    Q_INVOKABLE long removeFileInfos(long downloadIDs[]);
    /**
     * @brief restart 重新下载。
     * @param downloadID 要重新下载的任务Id。
     * @return 成功则重新下载后的新任务Id。
                失败则返回错误码。
     */
    Q_INVOKABLE long restart(long downloadID);
    /**
     * @brief resume 恢复下载 (暂不支持)。
     * @param downloadID 要恢复的下载任务Id
     * @return 成功则无返回。
                      失败则返回错误码。
     */
    Q_INVOKABLE long resume(long downloadID);
    /**
     * @brief start 开始下载
     * @param url 下载文件地址
     * @param name 保存的文件名
     * @return 成功则下载任务Id。
                     失败则返回错误码。
     */
    Q_INVOKABLE long start(long downloadID,QString url, QString name);

signals:
    /**
     * @brief downloadCanceled 添加监听下载取消事件
     * @param downloadID 下载任务的Id
     */
    void downloadCanceled(long downloadID);
    /**
     * @brief downloadCompleted 添加监听下载完成事件
     * @param downloadID 下载任务的Id
     * @param path 下载任务的路径
     */
    void downloadCompleted(long downloadID, QString path);
    /**
     * @brief downloadFailed 添加监听下载失败事件
     * @param downloadID 下载任务的Id
     * @param result 下载任务失败的结果
     * @param errorCode 下载任务失败的错误码
     */
    void downloadFailed(long downloadID, QString result, long errorCode);
    /**
     * @brief downloadPaused 添加监听下载暂停事件
     * @param downloadID 下载任务的Id
     */
    void downloadPaused(long downloadID);
    /**
     * @brief downloadProgress 添加监听下载进度事件
     * @param downloadID 下载任务的Id
     * @param name 下载任务的文件名
     * @param receivedSize 下载任务已接收的大小
     * @param totalSize 下载任务总大小
     */
    void downloadProgress(long downloadID, QString name, double receivedSize, double totalSize);

public slots:

    void saveDownloadFile(QString url, QNetworkReply *reply);

    void downloadFileFailed(QString url, long errorCode, QString errorMessage);

private:
    long taskId;
    QMap<long, DownloadTask> downloadTasks;

    DownloadTask* findTaskByUrl(QString url);
};

#endif // DOWNLOAD_H
