#include "notification.h"
#include <QDebug>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <cbadge.h>
#include <cnotification.h>
#include <cnotificationmanager.h>
#include "framework/common/errorinfo.h"

using namespace NativeSdk;

Notification::Notification()
{
}


void Notification::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;
    if (actionName == "badgeShow") {
        badgeShow(callbackID, params);
    } else if (actionName == "sendNotification") {
        sendNotification(callbackID, params);
    } else if (actionName == "removeAllNotifications") {
        removeAllNotifications(callbackID, params);
    } else if (actionName == "removeNotification") {
        removeNotification(callbackID, params);
    }
}

void Notification::badgeShow(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "badgeShow" << params << endl;
    QString appId = params.value("appId").toString();
    long num = params.value("num").toInt();

    CBadge badge;
    badge.setValue(appId,num);

    signalManager()->success(callbackID.toLong(), true);
}

void Notification::sendNotification(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "sendNotification" << params << endl;
    long type = params.value("type").toInt();
    QString title = params.value("title").toString();
    QString subtitle = params.value("subtitle").toString();

    CNotification notification;
    notification.setTitle(title);
    notification.setSubtitle(subtitle);

    if (type == 1) {
        notification.setAttributes(CAbstractNotification::DeleteOnFinished);//通知在状态栏显示完成后， 自动删除
    } else if (type == 2) {
        notification.setAttributes(CAbstractNotification::HideDisplayTime);//通知发送时间不显示在下拉列表上
    } else if (type == 3) {
        notification.setAttributes(CAbstractNotification::DeleteOnReboot);//通知在手机重启后， 自动删除
    }
    notification.setVibrationMode(CAbstractNotification::ForceVibrationMode);//强制震动模式。 忽略系统的震动设置， 在通知发送是， 必须震动

    CNotificationManager notificationManager;
    QString updateId = notificationManager.sendNotification(notification);

    QJsonObject jsonObject;
    jsonObject.insert("updateId", updateId);
    QJsonValue::fromVariant(jsonObject);
    signalManager()->success(callbackID.toLong(), QVariant(jsonObject));
}

void Notification::removeAllNotifications(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "removeAllNotifications" << params << endl;

    CNotificationManager notificationManager;
    notificationManager.removeAllNotifications();

    signalManager()->success(callbackID.toLong(), true);
}

void Notification::removeNotification(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "removeNotification" << params << endl;
    QString updateId = params.value("updateId").toString();

    CNotificationManager notificationManager;
    notificationManager.removeNotification(updateId);

    signalManager()->success(callbackID.toLong(), true);
}
