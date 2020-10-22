#ifndef UPDATE_H
#define UPDATE_H

#include <QObject>
#include <QtPlugin>
#include <QNetworkReply>

#include "iplugin/iplugin.h"
#include "update_global.h"

class SyberH5HelpperPrivate;

class UPDATESHARED_EXPORT Update : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Update();
    ~Update();

    void invoke(QString callbackID, QString actionName, QVariantMap params);

private :

    /**
     * @brief check jiancha shi fou geng xin
     * @param callBackID 任务Id
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void check(QString callbackID,QVariantMap params);

    SyberH5HelpperPrivate *d;
    QString MY_APP_ID;
    QString NEW_VERSION_HEAD;
    QString CHECK_NEWVERSION;
    long checkCallBackID;

private slots:
    void handleNetworkAccessReply(QNetworkReply *reply);

};

#endif // UPDATE_H
