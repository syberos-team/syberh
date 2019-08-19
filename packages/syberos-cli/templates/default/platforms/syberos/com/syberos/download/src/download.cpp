#include "download.h"
#include "helper.h"
#include "httpclient.h"
#include <QObject>
#include <QDebug>
#include <QDir>

Download::Download(QObject *parent) : QObject(parent) {

    connect(HttpClient::instance(), &HttpClient::replyData, this, &Download::saveDownloadFile);
    connect(HttpClient::instance(), &HttpClient::replyError, this, &Download::downloadFileFailed);
}

Download* Download::instance(){
    static Download download;
    return &download;
}

QString Download::getDownloadDir(){
    return Helper::instance()->getInnerStorageRootPath();
}

/**
 * @brief cancel 取消下载
 * @param downloadID 要取消下载的任务Id
 * @return 成功则无返回。
 *      失败则返回错误码。
 */
long Download::cancel(long downloadID){
    return downloadID;
}
/**
 * @brief getFileInfos 获取所有下载文件信息
 * @return 成功则返回FileInfo数组。
          失败则返回错误码。
 */
QList<FileInfo> Download::getFileInfos(){
    QList<FileInfo> list;
    return list;
}
/**
 * @brief pause 暂停下载 (暂不支持)
 * @param downloadID 要暂停的下载任务Id
 * @return 成功则无返回。
                  失败则返回错误码。
 */
long Download::pause(long downloadID){
    return downloadID;
}
/**
 * @brief removeFileInfos 移除下载文件记录。
 * @param downloadIDs 整型数组, 要移除下载文件的Id。
 * @return 成功则无返回。
                  失败则返回错误码。
 */
long Download::removeFileInfos(long downloadIDs[]){
    return downloadIDs[0];
}
/**
 * @brief restart 重新下载。
 * @param downloadID 要重新下载的任务Id。
 * @return 成功则重新下载后的新任务Id。
            失败则返回错误码。
 */
long Download::restart(long downloadID){
    return downloadID;
}
/**
 * @brief resume 恢复下载 (暂不支持)。
 * @param downloadID 要恢复的下载任务Id
 * @return 成功则无返回。
                  失败则返回错误码。
 */
long Download::resume(long downloadID){
    return downloadID;
}
/**
 * @brief start 开始下载
 * @param url 下载文件地址
 * @param name 保存的文件名
 * @return 成功则下载任务Id。
                 失败则返回错误码。
 */
long Download::start(long downloadID,QString url, QString name){
    taskId += 1;
    DownloadTask task;
    task.downloadID = downloadID;
    task.url = url;
    task.name = name;

    HttpClient::instance()->get(url);

    downloadTasks[downloadID] = task;
    return taskId;
}


DownloadTask* Download::findTaskByUrl(QString url){
    QMap<long, DownloadTask>::const_iterator it = downloadTasks.begin();
    while(it != downloadTasks.end()){
        DownloadTask task = it.value();
        if(url == task.url){
            downloadTasks.remove(task.downloadID);
            return new DownloadTask(task);
        }
    }
    return NULL;
}


// 槽，保存下载的文件
void Download::saveDownloadFile(QString url, QNetworkReply *reply){
    qDebug() << Q_FUNC_INFO << " url: " << url << endl;

    QString path = getDownloadDir() + "/download";
    QDir dir(path);
    if(!dir.exists()){
        dir.mkpath(path);
    }

    DownloadTask* task = findTaskByUrl(url);
    if(NULL == task){
        qDebug() << Q_FUNC_INFO << "cannot found task by url:" << url << endl;
        return;
    }
    QString filename = task->name;
    long downloadID = task->downloadID;
    delete task;

//    connect(reply, &QNetworkReply::downloadProgress, this, [](long downloadID, QString filename)->{
//        emit downloadProgress(downloadID, filename, );
//    });

    QString filePath = path + "/" + filename;
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << Q_FUNC_INFO << " save fail: " << file.error() << file.errorString() << endl;
        return;
    }
    file.write(reply->readAll());
    file.close();

    reply->deleteLater();
    emit downloadCompleted(downloadID, filePath);
}


void Download::downloadFileFailed(QString url, long errorCode, QString errorMessage){
    qDebug() << Q_FUNC_INFO << " url:" << url << "error: " << errorCode << errorMessage << endl;

    DownloadTask* task = findTaskByUrl(url);
    if(NULL == task){
        qDebug() << Q_FUNC_INFO << "cannot found task by url:" << url << endl;
        return;
    }
    long downloadID = task->downloadID;
    delete task;
    emit downloadFailed(downloadID, errorMessage, errorCode);
}
