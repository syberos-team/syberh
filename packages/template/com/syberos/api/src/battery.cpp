#include "battery.h"
#include <QObject>
#include <QDebug>
#include <cosinfo.h>
#include <csystemdeviceinfo.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <cbatterymanager.h>

int Battery::typeId = qRegisterMetaType<Battery *>();
Battery::Battery()
{

}
Battery::~Battery()
{

}

void Battery::request(QString callBackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "callbackId:" << callBackID << "actionName:" << actionName << "params:" << params << endl;

    //如果参数不使用此方法可以防止运行异常
    Q_UNUSED(actionName);
    Q_UNUSED(params);
    getStatus(callBackID.toLong(), params);

}

void Battery::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID);
    Q_UNUSED(callBackID);
    Q_UNUSED(actionName);
    Q_UNUSED(dataRowList);
    Q_UNUSED(attachementes);

}

void Battery::getStatus(long callBackID,QVariantMap params){
    Q_UNUSED(callBackID);
    Q_UNUSED(params);

    CBatteryManager battery;
    int capacity = battery.capacity();
    int level = battery.level();
    bool isValid = battery.isValid();
    bool isCharging = battery.isCharging();

    QJsonObject json;
    json.insert("isCharging", isCharging);
    json.insert("level", level);
    json.insert("capacity", capacity);
    json.insert("isValid", isValid);

    qDebug() << "getStatus: " << json << endl;

    emit success(callBackID, QVariant(json));
}

