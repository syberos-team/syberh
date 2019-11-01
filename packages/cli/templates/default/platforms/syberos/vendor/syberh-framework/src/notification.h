#ifndef MESSAGENOTIFICATION_H
#define MESSAGENOTIFICATION_H

#include "cbadge.h"
#include "cnotification.h"
#include "cnotificationmanager.h"
#include "framework/nativesdkhandlerbase.h"

class Notification : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Notification();
    ~Notification();

    void request(QString callBackID,QString actionName,QVariantMap params);
    void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);

private :

    /**
     * @brief badgeShow 角标显示
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void badgeShow(long callBackID, QVariantMap params);

    /**
     * @brief sendNotification 消息发送
     * @param params 参数
     * @return 成功则消息id。
     *      失败则返回错误码。
     */
    void sendNotification(long callBackID, QVariantMap params);

    /**
     * @brief removeAllNotifications 删除消息
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void removeAllNotifications(long callBackID, QVariantMap params);

    /**
     * @brief removeNotification 删除指定消息
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void removeNotification(long callBackID, QVariantMap params);

    static int typeId;
};

#endif // MESSAGENOTIFICATION_H
