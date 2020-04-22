#include "networkstatus.h"
#include <QDebug>
#include <cnetworkmanager.h>

namespace NativeSdk {

NetworkStatus *NetworkStatus::m_pNetworkStatus = NULL;

NetworkStatus::NetworkStatus(QObject *parent):QObject(parent)
{
    m_nNetWorkManager = new CNetworkManager();
    connect(m_nNetWorkManager, &CNetworkManager::networkStatusChanged,
            this,  [this](bool connected, CNetworkManager::NetworkType type){
        int typeInt = type;
        slotNetworkStatusChanged(connected, static_cast<NetworkStatus::NetworkType>(typeInt));
    });

    CNetworkManager::NetworkType type = m_nNetWorkManager->currentNetworkType();
    if(type == CNetworkManager::Cellular)
        m_nConnectNetworkType = "cellular";
    else if (type == CNetworkManager::Wifi)
        m_nConnectNetworkType = "wifi";
    else
        m_nConnectNetworkType = "";
}

NetworkStatus* NetworkStatus::getInstance(){
    if(m_pNetworkStatus == NULL)
        m_pNetworkStatus = new NetworkStatus();
    return m_pNetworkStatus;
}

NetworkStatus::~NetworkStatus()
{
    if(m_pNetworkStatus != NULL){
        delete m_pNetworkStatus;
        m_pNetworkStatus = NULL;
    }
    if(m_nNetWorkManager != NULL){
        delete m_nNetWorkManager;
        m_nNetWorkManager = NULL;
    }
}

void NetworkStatus::slotNetworkStatusChanged(bool flag, NetworkType type)
{
    Q_UNUSED(flag)
    if(type ==  Cellular)
        m_nConnectNetworkType = "cellular";
    else if(type == Wifi)
        m_nConnectNetworkType = "wifi";
    else
        m_nConnectNetworkType = "";
   emit networkConnectChanged(m_nConnectNetworkType);
}

QString NetworkStatus::getNetworkConnectStatus()
{
    return m_nConnectNetworkType;
}

}
