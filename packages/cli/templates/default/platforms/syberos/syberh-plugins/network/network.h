#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QtPlugin>
#include <QNetworkAccessManager>

#include "iplugin/iplugin.h"
#include "network_global.h"


class TaskInfo
{
public:
    QString dataType;
    QNetworkReply* reply;

};

class NETWORKSHARED_EXPORT Network: public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Network();
    ~Network();

    void invoke(QString callbackID, QString actionName, QVariantMap params);

private :
    QNetworkAccessManager *manager;

    QMap<QString,TaskInfo*> tasks; 
    
public slots:
    void finished(QNetworkReply *reply);
};

#endif // NETWORK_H
