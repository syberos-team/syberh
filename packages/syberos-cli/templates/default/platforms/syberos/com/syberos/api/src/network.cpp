#include "network.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QJsonObject>

int NetWork::typeId = qRegisterMetaType<NetWork *>();

NetWork::NetWork()
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finished(QNetworkReply*)));
}
NetWork::~NetWork()
{
    delete manager;
}
void NetWork::request(QString callBackID, QString actionName, QVariantMap params)
{

    // 检查网络
    if (!netWorkConnected()) {
        emit failed(callBackID.toLong(),NETWORK_ERROR,ErrorInfo::m_errorCode.value(NETWORK_ERROR));
        return;
    }

    qDebug() << Q_FUNC_INFO << "NetWork callbackID is" << callBackID << "actionName is" << actionName << "params is" << params << endl;

    QString url = params.value("url").toString();
    QString method = params.value("method").toString();
    if (method == "") {
        qDebug() << Q_FUNC_INFO << "params type is null, set default values: get callbackID is " << callBackID << endl;
        method = "get";
    }

    QNetworkReply *reply;

    QNetworkRequest request;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::UnknownProtocol);
    request.setSslConfiguration(config);

//    QVariantMap headers = params.value("headers").toMap();
//    QVariantMap::Iterator headerIt = headers.begin();
//    while (headerIt != headers.end()) {
//        request.setHeader(headerIt.key(), headerIt.value().toString());
//        headerIt++;
//    }
//    if (!headers.contains("content-type")){
//        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
//    }

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    request.setUrl(url);

    if ("get" == method.toLower()) {
        reply = manager->get(request);
    } else if ("post" == method.toLower()) {
        QVariantMap data = params.value("data").toMap();

        QVariantMap::Iterator it = data.begin();

        QString content;

        while (it != data.end()) {
            content.append(it.key()).append("=").append(it.value().toString());
            it++;
            if (it != data.end()) {
                content.append("&");
            }
        }
        qDebug() << Q_FUNC_INFO << "param type is post, param data is :" << data << "content is :" << content << endl;

        request.setHeader(QNetworkRequest::ContentLengthHeader, content.length());

        reply = manager->post(request, content.toUtf8());
    } else {
        emit failed(callBackID.toLong(), 500, "Invalid type param");
        return;
    }

    TaskInfo taskInfo;
    taskInfo.callBackID = callBackID;
    taskInfo.reply = reply;
    tasks[callBackID] = taskInfo;

}


void NetWork::finished(QNetworkReply *reply)
{
    qDebug() << Q_FUNC_INFO << endl;

    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    qDebug() << Q_FUNC_INFO << " statusCode: " << statusCode.toString() << " error: " << reply->error() << endl;

    QString result = QString(reply->readAll());

    qDebug() << Q_FUNC_INFO << " result: " << result << " url:" << reply->url().url() <<endl;

    QString callBackId;

    QMap<QString, TaskInfo>::Iterator it = tasks.begin();
    while(it != tasks.end()){
        TaskInfo taskInfo = it.value();
        if (taskInfo.reply == reply) {
            callBackId = taskInfo.callBackID;
            tasks.remove(it.key());
            break;
        }
        it++;
    }
    qDebug() << Q_FUNC_INFO << " tasks.size(): " << tasks.size() <<endl;
    qDebug() << Q_FUNC_INFO << " callBackId: " << callBackId <<endl;

    if(QNetworkReply::NoError == reply->error()) {
        QJsonObject json;
        json.insert("data", result);
        emit success(callBackId.toLong(), json);
    }else{
        qDebug() << Q_FUNC_INFO << " result error " <<endl;
        emit failed(callBackId.toLong(), 500, reply->errorString());
    }
}
