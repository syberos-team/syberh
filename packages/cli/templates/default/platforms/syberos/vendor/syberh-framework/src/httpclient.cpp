#include "httpclient.h"
#include <QNetworkAccessManager>
#include <QDebug>
#include "cenvironment.h"

HttpClient::HttpClient(QObject *parent) :
    QObject(parent) {
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &HttpClient::finished);
}

HttpClient::~HttpClient(){
    delete manager;
    manager = NULL;
}


QNetworkReply* HttpClient::get(const QString &url){
    qDebug() << Q_FUNC_INFO << endl;
    QUrl qurl(url);
    QNetworkRequest request(qurl);

    QString urlAddr = url.toLower();
    if(urlAddr.startsWith("https")){
        QSslConfiguration config;
        config.setPeerVerifyMode(QSslSocket::VerifyNone);
        config.setProtocol(QSsl::UnknownProtocol);
        request.setSslConfiguration(config);
    }
    return manager->get(request);
}

void HttpClient::finished(QNetworkReply *reply){
    qDebug() << Q_FUNC_INFO << endl;

    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    qDebug() << Q_FUNC_INFO << " statusCode: " << statusCode.toString() << " error: " << reply->error() << endl;

    if(QNetworkReply::NoError == reply->error()) {
        emit replyData(reply->url().toString(), reply);
    }else{
        emit replyError(reply->url().toString(), reply->error(), reply->errorString());
    }
}

