#include "uploadmanager.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QHttpMultiPart>
#include <QDebug>
#include "../../../syberh-framework/src/framework/common/errorinfo.h"

UploadManager::UploadManager()
{
    m_networkManager = new QNetworkAccessManager(this);
    m_isStop = false;
}
UploadManager::~UploadManager()
{
    m_networkManager->deleteLater();
    m_networkManager = NULL;
    m_file->deleteLater();
    m_file = NULL;
    m_multiPart->deleteLater();
    m_multiPart = NULL;
}

void UploadManager::setUploadId(QString uploadId)
{
    m_uploadId = uploadId;
}

void UploadManager::uploadFile(QString reqUrl, QString localFile)
{

    qDebug() << Q_FUNC_INFO << "上传文件地址：" + reqUrl + ",本地文件地址:" + localFile << endl;

    m_file = new QFile(localFile) ;
    if (!m_file->exists()) {
        emit signalError(m_uploadId, ErrorInfo::FileNotExists, ErrorInfo::message(ErrorInfo::FileNotExists));
        return;
    }

    m_multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    m_file->open(QIODevice::ReadOnly);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\""+m_file->fileName()+"\""));

    imagePart.setBodyDevice(m_file);

    m_file->setParent(m_multiPart);

    m_multiPart->append(imagePart);

    QNetworkRequest request;

    QString urlAddr = reqUrl.toLower();
    if(urlAddr.startsWith("https")){
        QSslConfiguration config;
        config.setPeerVerifyMode(QSslSocket::VerifyNone);
        config.setProtocol(QSsl::UnknownProtocol);
        request.setSslConfiguration(config);
    }
    request.setUrl(reqUrl);


    m_reply = m_networkManager->post(request, m_multiPart);

    emit signalStarted(m_uploadId);

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
    Q_UNUSED(code)
//    qDebug() << Q_FUNC_INFO << "upload failed " << code << endl;
    m_isStop = true;

    emit signalError(m_uploadId, ErrorInfo::NetworkError, ErrorInfo::message(ErrorInfo::NetworkError, m_reply->errorString()) );
}


