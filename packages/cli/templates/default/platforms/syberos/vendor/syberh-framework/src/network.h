#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include "framework/nativesdkhandlerbase.h"
#include <QObject>
#include <QtNetwork>


class TaskInfo
{
public:
    QString dataType;
    QNetworkReply* reply;

};


class Network : public NativeSdkHandlerBase
{
    Q_OBJECT

public:

    Q_INVOKABLE Network();
    ~Network();

    void request(QString callBackID,QString actionName,QVariantMap params);

    static int typeId;

private :
    QNetworkAccessManager *manager;

    QMap<QString,TaskInfo*> tasks;

public slots:
    void finished(QNetworkReply *reply);
};

#endif // NETWORKHANDLER_H
