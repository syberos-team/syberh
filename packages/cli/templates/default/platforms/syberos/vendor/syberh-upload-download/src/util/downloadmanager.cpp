#include "downloadmanager.h"
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include "../../../syberh-framework/src/framework/common/errorinfo.h"

#define DATETIME_FMT "yyyyMMddhhmmss"

DownloadManager::DownloadManager(QObject *parent) : QObject(parent)
        , m_networkManager(NULL)
        , m_url("")
        , m_fileName("")
        , m_isSupportBreakPoint(false)
        , m_bytesReceived(0)
        , m_bytesTotal(0)
        , m_bytesCurrentReceived(0)
        , m_isStop(true)
        , m_downloadId("")
        , m_storage(Internal)
{
    m_tmpFileSuffix = "." + QDateTime::currentDateTime().toString(DATETIME_FMT);

    m_networkManager = new QNetworkAccessManager(this);
    m_storageManager = new CStorageManager(this);
}


DownloadManager::~DownloadManager(){
    m_storageManager->deleteLater();
    m_storageManager = NULL;
    m_networkManager->deleteLater();
    m_networkManager = NULL;
}

// 设置是否支持断点续传
void DownloadManager::setDownInto(bool isSupportBreakPoint){
    m_isSupportBreakPoint = isSupportBreakPoint;
}

// 获取当前下载链接
QString DownloadManager::getDownloadUrl(){
    return m_url.toString();
}
// 获取临时文件后缀
QString DownloadManager::getDownloadFileSuffix() {
    return m_tmpFileSuffix;
}

// 开始下载文件，传入下载链接和文件的路径
void DownloadManager::downloadFile(QString url , QString fileName){
    // 防止多次点击开始下载按钮，进行多次下载，只有在停止标志变量为true时才进行下载;
    if (m_isStop) {
        m_isStop = false;
        m_url = QUrl(url);

        // 这里可用从url中获取文件名，但不是对所有的url都有效;
//      QString fileName = m_url.fileName();

        // 将当前文件名设置为临时文件名，下载完成时修改回来;
        m_fileName = fileName + m_tmpFileSuffix;

        m_path = fileName;

        QFileInfo f(m_path);
        if(f.isDir()){
            emit signalDownloadError(m_downloadId, ErrorInfo::IllegalFileType, ErrorInfo::message(ErrorInfo::IllegalFileType, "必须是一个文件路径"));
            return;
        }
        //自动创建目录
        QDir dir( f.absoluteDir());
        if(!dir.exists()){
            dir.mkpath(dir.absolutePath());
        }

        // 如果当前下载的字节数为0那么说明未下载过或者重新下载
        // 则需要检测本地是否存在之前下载的临时文件，如果有则删除
        if (m_bytesCurrentReceived <= 0) {
            removeFile(m_fileName);
        }

        QNetworkRequest request;

        QString urlAddr = m_url.url().toLower();
        if(urlAddr.startsWith("https")){
            QSslConfiguration config;
            config.setPeerVerifyMode(QSslSocket::VerifyNone);
            config.setProtocol(QSsl::UnknownProtocol);
            request.setSslConfiguration(config);
        }
        request.setUrl(m_url);

        // 如果支持断点续传，则设置请求头信息
        if (m_isSupportBreakPoint) {
            QString strRange = QString("bytes=%1-").arg(m_bytesCurrentReceived);
            request.setRawHeader("Range", strRange.toLatin1());
        }

        // 请求下载;
        m_reply = m_networkManager->get(request);

        emit signalStarted(m_downloadId, m_path);

        connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
        connect(m_reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
        connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));


    }
}

// 停止下载工作
void DownloadManager::stopWork(){
    m_isStop = true;
    if (m_reply != NULL) {
        disconnect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
        disconnect(m_reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        disconnect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
        disconnect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
        m_reply->abort();
        m_reply->deleteLater();
        m_reply = NULL;
    }
}

// 暂停下载按钮被按下,暂停当前下载
void DownloadManager::stopDownload(){
    // 这里m_isStop变量为了保护多次点击暂停下载按钮，导致m_bytesCurrentReceived 被不停累加;
    if (!m_isStop) {
        //记录当前已经下载字节数
        m_bytesCurrentReceived += m_bytesReceived;
        stopWork();
    }
}

// 重置参数
void DownloadManager::reset(){
    m_bytesCurrentReceived = 0;
    m_bytesReceived = 0;
    m_bytesTotal = 0;
}

// 删除文件
void DownloadManager::removeFile(QString fileName){
    // 删除已下载的临时文件;
    QFileInfo fileInfo(fileName);
    if (fileInfo.exists()) {
        QFile::remove(fileName);
    }
}

// 停止下载按钮被按下，关闭下载，重置参数，并删除下载的临时文件
void DownloadManager::closeDownload(){
    stopWork();
    reset();
    removeFile(m_fileName);
}

void DownloadManager::setDownloadId(QString downloadId){
    m_downloadId = downloadId;
}

void DownloadManager::setStorage(DownloadManager::Storage storage){
    m_storage = storage;
}

DownloadManager::Storage DownloadManager::getStorage() {
    return m_storage;
}

QString DownloadManager::getDownloadId(){
    return m_downloadId;
}

QString DownloadManager::getMPath(){
    return m_path;
}

qint64 DownloadManager::getBytesReceived(){
    return m_bytesReceived;
}

qint64 DownloadManager::getBytesTotal(){
    return m_bytesTotal;
}


//获取下载文件大小
qint64 DownloadManager::downloadFileSize(){
    if(m_bytesTotal > 0){
        return m_bytesTotal;
    }
    QVariant size = m_reply->header(QNetworkRequest::ContentLengthHeader);
    if (size.isValid()){
        m_bytesTotal = size.toLongLong();
    }
    return m_bytesTotal;
}

//获取存储空间剩余
qint64 DownloadManager::storageFreeSize(){
    if(m_storageFreeSize > 0){
        return m_storageFreeSize;
    }
    m_storageFreeSize = m_storageManager->storageFreeSize(m_storage==Extended ? CStorageManager::ExtStorage : CStorageManager::IntStorage);
    return m_storageFreeSize;
}


// 下载进度信息
void DownloadManager::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal){
    if (!m_isStop) {
        m_bytesReceived = bytesReceived;
        m_bytesTotal = bytesTotal;
        // 更新下载进度;(加上 m_bytesCurrentReceived 是为了断点续传时之前下载的字节)
        emit signalDownloadProcess(m_downloadId, m_path, m_bytesReceived + m_bytesCurrentReceived, m_bytesTotal + m_bytesCurrentReceived);
    }
}

// 获取下载内容，保存到文件中
void DownloadManager::onReadyRead(){
    if (!m_isStop) {
        QFile file(m_fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
            qint64 free = storageFreeSize();
            qint64 size = downloadFileSize();
            if(size > free){
                qDebug() << Q_FUNC_INFO << "存储空间不足，预期：" << size << "，实际可用：" << free << endl;
                emit signalDownloadError(m_downloadId, ErrorInfo::NotEnoughSpace, ErrorInfo::message(ErrorInfo::NotEnoughSpace, "存储空间不足"));
                closeDownload();
            }else{
                file.write(m_reply->readAll());
            }
        }
        file.close();
    }
}
// 下载完成
void DownloadManager::onFinished(){
    m_isStop = true;
    // http请求状态码;
    QVariant statusCode = m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    QString errorMessage;
    if (m_reply->error() == QNetworkReply::NoError) {
        // 重命名临时文件;
        QFileInfo fileInfo(m_fileName);
        if (fileInfo.exists()) {
            int index = m_fileName.lastIndexOf(m_tmpFileSuffix);
            QString realName = m_fileName.left(index);
            QFile::rename(m_fileName, realName);
        }
    } else {
        // 有错误输出错误;
        errorMessage = m_reply->errorString();
    }

    emit signalReplyFinished(m_downloadId, m_path, statusCode.toInt(), errorMessage);
}

// 下载过程中出现错误，关闭下载，并上报错误，这里未上报错误类型，可自己定义进行上报;
void DownloadManager::onError(QNetworkReply::NetworkError code){
    Q_UNUSED(code)
    qDebug () << Q_FUNC_INFO << "下载过程中出现错误：" << m_reply->errorString() <<endl;
    emit signalDownloadError(m_downloadId, ErrorInfo::NetworkError, ErrorInfo::message(ErrorInfo::NetworkError, m_reply->errorString()));
    closeDownload();
}
