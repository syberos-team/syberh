#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>
#include <QtPlugin>

#include "iplugin/iplugin.h"
#include "notification_global.h"

class NOTIFICATIONSHARED_EXPORT Notification: public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Notification();

    void invoke(QString callbackID, QString actionName, QVariantMap params);

private :
    /**
     * @brief badgeShow 角标显示
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void badgeShow(QString callbackID, QVariantMap params);

    /**
     * @brief sendNotification 消息发送
     * @param params 参数
     * @return 成功则消息id。
     *      失败则返回错误码。
     */
    void sendNotification(QString callbackID, QVariantMap params);

    /**
     * @brief removeAllNotifications 删除消息
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void removeAllNotifications(QString callbackID, QVariantMap params);

    /**
     * @brief removeNotification 删除指定消息
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void removeNotification(QString callbackID, QVariantMap params);

};

#endif // NOTIFICATION_H
