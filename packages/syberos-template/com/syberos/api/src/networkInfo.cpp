#include "networkInfo.h"
#include <QObject>
#include <QDebug>
#include <qjsonobject.h>




int NetworkInfo::typeId = qRegisterMetaType<NetworkInfo *>();
NetworkInfo::NetworkInfo()
{
#include <qjsonobject.h>
}
NetworkInfo::~NetworkInfo()
{

}

void NetworkInfo::request(QString callBackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "callbackId:" << callBackID << "actionName:" << actionName << "params:" << params << endl;

    //如果参数不使用此方法可以防止运行异常
    Q_UNUSED(actionName);
    Q_UNUSED(params);
    getInfo(callBackID.toLong(), params);

}

void NetworkInfo::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID);
    Q_UNUSED(callBackID);
    Q_UNUSED(actionName);
    Q_UNUSED(dataRowList);
    Q_UNUSED(attachementes);

}

void NetworkInfo::getInfo(long callBackID,QVariantMap params){
    Q_UNUSED(callBackID);
    Q_UNUSED(params);


    CNetworkManager network;
    bool isNetworkAvailable = network.isNetworkAvailable();
    bool isWifiConnected = network.isWifiConnected();
//    int networkType = CNetworkManager::NetworkType;
    int wifiSignalStrength = network.wifiSignalStrength();
    int networkType = network.currentNetworkType();

    QJsonObject json;
    json.insert("networkType", networkType);
    json.insert("isNetworkAvailable", isNetworkAvailable);
    json.insert("isWifiConnected", isWifiConnected);
    json.insert("wifiSignalStrength", wifiSignalStrength);

    qDebug() << "getInfo: " << json << endl;

    emit success(callBackID, json);
}

