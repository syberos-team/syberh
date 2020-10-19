#include "networkinfo.h"
#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <cnetworkmanager.h>

NetworkInfo::NetworkInfo()
{
}


void NetworkInfo::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    if (actionName == "info") {
        info(callbackID, params);
    }
}

void NetworkInfo::info(QString callbackID,QVariantMap params){
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

    qDebug() << Q_FUNC_INFO << "json:" << json << endl;
    signalManager()->success(callbackID.toLong(),  QVariant(json));
}

