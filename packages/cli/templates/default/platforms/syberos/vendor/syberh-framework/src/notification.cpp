#include "notification.h"

#include <QDebug>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include "framework/common/errorinfo.h"

int Notification::typeId = qRegisterMetaType<Notification *>();

Notification::Notification(){}
Notification::~Notification(){}

void Notification::request(QString callBackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "request" << callBackID << endl;
    if (actionName == "badgeShow"){
        badgeShow(callBackID.toLong(), params);
    }else if(actionName == "sendNotification"){
        sendNotification(callBackID.toLong(), params);
    }else if(actionName == "removeAllNotifications"){
        removeAllNotifications(callBackID.toLong(), params);
    }else if(actionName == "removeNotification"){
        removeNotification(callBackID.toLong(), params);
    }
}

void Notification::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
}

void Notification::badgeShow(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "badgeShow" << params << endl;
    QString appId = params.value("appId").toString();
    long num = params.value("num").toInt();

    CBadge badge;
    badge.setValue(appId,num);

    emit success(callBackID, true);
}

void Notification::sendNotification(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "sendNotification" << params << endl;
    long type = params.value("type").toInt();
    QString title = params.value("title").toString();
    QString subtitle = params.value("subtitle").toString();

    CNotification notification;
    notification.setTitle(title);
    notification.setSubtitle(subtitle);

    if(type == 1){
        notification.setAttributes(CAbstractNotification::DeleteOnFinished);//通知在状态栏显示完成后， 自动删除
    }else if(type == 2){
        notification.setAttributes(CAbstractNotification::HideDisplayTime);//通知发送时间不显示在下拉列表上
    }else if(type == 3){
        notification.setAttributes(CAbstractNotification::DeleteOnReboot);//通知在手机重启后， 自动删除
    }
    notification.setVibrationMode(CAbstractNotification::ForceVibrationMode);//强制震动模式。 忽略系统的震动设置， 在通知发送是， 必须震动

    CNotificationManager notificationManager;
    QString updateId = notificationManager.sendNotification(notification);

    QJsonObject jsonObject;
    jsonObject.insert("updateId", updateId);
    QJsonValue::fromVariant(jsonObject);
    emit success(callBackID, QVariant(jsonObject));
}

void Notification::removeAllNotifications(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "removeAllNotifications" << params << endl;

    CNotificationManager notificationManager;
    notificationManager.removeAllNotifications();

    emit success(callBackID, true);
}

void Notification::removeNotification(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "removeNotification" << params << endl;
    QString updateId = params.value("updateId").toString();

    CNotificationManager notificationManager;
    notificationManager.removeNotification(updateId);

    emit success(callBackID, true);
}
