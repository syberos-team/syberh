#include "cellular.h"
#include <QObject>
#include <QDebug>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <csystemnetworkmanager.h>

int Cellular::typeId = qRegisterMetaType<Cellular *>();
Cellular::Cellular()
{
}
Cellular::~Cellular()
{

}

void Cellular::request(QString callBackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "callbackId:" << callBackID << "actionName:" << actionName << "params:" << params << endl;

    //如果参数不使用此方法可以防止运行异常
    Q_UNUSED(params);
    if (actionName=="networkEnabled"){
        networkEnabled(callBackID.toLong(), params);
    }else if (actionName=="networkDisabled"){
        networkDisabled(callBackID.toLong(), params);
    }

}

void Cellular::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID);
    Q_UNUSED(callBackID);
    Q_UNUSED(actionName);
    Q_UNUSED(dataRowList);
    Q_UNUSED(attachementes);

}


void Cellular::networkDisabled(long callBackID,QVariantMap params){

    qDebug() << "NetworkSetCellularEnabled callbackID is" << callBackID << "params is" << params << endl;

    bool flag = false;

    CSystemNetworkManager networkManager;
    //true 表示可用， false 表示禁用。
    bool isDisabled = networkManager.setCellularEnabled(flag);

    QJsonObject json;
    json.insert("isDisabled", isDisabled);

    qDebug() << "isDisabled: " << isDisabled << endl;

    emit success(callBackID,  json);
}


void Cellular::networkEnabled(long callBackID,QVariantMap params){

    qDebug() << "NetworkSetCellularEnabled callbackID is" << callBackID << "params is" << params << endl;

    bool flag = true;

    CSystemNetworkManager networkManager;
    //true 表示可用， false 表示禁用。
    bool isEnabled = networkManager.setCellularEnabled(flag);

    QJsonObject json;
    json.insert("isEnabled", isEnabled);

    qDebug() << "isEnabled: " << isEnabled << endl;

    emit success(callBackID,  json);
}

