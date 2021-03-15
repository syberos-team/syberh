#include "networkstatus.h"
#include <QDebug>
#include <cnetworkmanager.h>

namespace NativeSdk {

inline NetworkStatus::NetworkType convertNetworkType(CNetworkManager::NetworkType networkType)
{
    int typeInt = static_cast<int>(networkType);
    return static_cast<NetworkStatus::NetworkType>(typeInt);
}


NetworkStatus *NetworkStatus::m_networkStatus = NULL;

NetworkStatus::NetworkStatus(QObject *parent):QObject(parent)
{
    m_newworkManager = new CNetworkManager();
    connect(m_newworkManager,
            &CNetworkManager::networkStatusChanged,
            this,
            [this](bool connected, CNetworkManager::NetworkType type){
                slotNetworkStatusChanged(connected, convertNetworkType(type));
            });

    CNetworkManager::NetworkType type = m_newworkManager->currentNetworkType();
    m_networkType = convertNetworkType(type);
}

NetworkStatus* NetworkStatus::getInstance()
{
    if(m_networkStatus == NULL)
        m_networkStatus = new NetworkStatus();
    return m_networkStatus;
}

NetworkStatus::~NetworkStatus()
{
    if(m_newworkManager != NULL){
        delete m_newworkManager;
        m_newworkManager = NULL;
    }
    if(m_networkStatus != NULL){
        delete m_networkStatus;
        m_networkStatus = NULL;
    }
}

void NetworkStatus::slotNetworkStatusChanged(bool flag, NetworkType type)
{
    Q_UNUSED(flag)
    m_networkType = type;
    emit networkConnectChanged(m_networkType);
}

QString NetworkStatus::getNetworkConnectStatus()
{
    switch (m_networkType)
    {
    case Cellular:
        return "cellular";
    case Wifi:
        return "wifi";
    case Ethernet:
        return "ethernet";
    default:
        return "";
    }
}

NetworkStatus::NetworkType NetworkStatus::getNetworkConnectType()
{
    return m_networkType;
}

}
