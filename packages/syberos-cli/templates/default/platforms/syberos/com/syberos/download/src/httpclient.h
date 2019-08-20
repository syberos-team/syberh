#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QMap>

class HttpClient : public QObject
{
    Q_OBJECT
public:
    static HttpClient* instance();
    ~HttpClient();

    QNetworkReply* get(const QString &url);

private:
    explicit HttpClient(QObject *parent = 0);
    HttpClient(const HttpClient &) Q_DECL_EQ_DELETE;
    HttpClient& operator=(HttpClient client) Q_DECL_EQ_DELETE;

    QNetworkAccessManager *manager;

signals:
    void replyData(QString url, QNetworkReply *reply);
    void replyError(QString url, long errorCode, QString errorMessage);

public slots:
    void finished(QNetworkReply *reply);
};

#endif // HTTPCLIENT_H
