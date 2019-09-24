#include "uploadmanager.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QHttpMultiPart>
#include <QDebug>

UploadManager::UploadManager()
{
    m_networkManager = new QNetworkAccessManager(this);
    m_isStop = false;
}
UploadManager::~UploadManager()
{
    m_networkManager->deleteLater();
    m_networkManager = NULL;
}

void UploadManager::setUploadId(QString uploadId)
{
    m_uploadId = uploadId;
}

void UploadManager::uploadFile(QString reqUrl, QString localFile)
{

//    qDebug() << Q_FUNC_INFO << "上传文件地址：" + reqUrl + ",本地文件地址:" + localFile << endl;

    QFile *file = new QFile(localFile) ;
    if (!file->exists()) {
        emit signalError(m_uploadId, 0, "上传文件不存在");
        return;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    file->open(QIODevice::ReadOnly);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\""+file->fileName()+"\""));

    imagePart.setBodyDevice(file);

    file->setParent(multiPart);

    multiPart->append(imagePart);

    QUrl url(reqUrl);
    QNetworkRequest request(url);

    m_reply = m_networkManager->post(request, multiPart);

    connect(m_reply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(onUploadProgress(qint64, qint64)));
    connect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
}

void UploadManager::stopWork()
{
    if (m_reply != NULL) {

        m_isStop = true;

        disconnect(m_reply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(onUploadProgress(qint64, qint64)));
        disconnect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
        disconnect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
        m_reply->abort();
        m_reply->deleteLater();
        m_reply = NULL;
    }
}

void UploadManager::onUploadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (!m_isStop) {
        m_bytesTotal = bytesTotal;
        emit signalUploadProcess(m_uploadId, bytesReceived, bytesTotal);
    }
}
void UploadManager::onFinished()
{
    if (!m_isStop) {
        emit signalReplyFinished(m_uploadId);
    }
}
void UploadManager::onError(QNetworkReply::NetworkError code)
{
//    qDebug() << Q_FUNC_INFO << "upload failed " << code << endl;
    m_isStop = true;
    emit signalError(m_uploadId, 500, m_reply->errorString());
}


