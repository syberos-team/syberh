#include "networkstatus.h"
#include <QDebug>

NetworkStatus *NetworkStatus::m_pNetworkStatus = NULL;
NetworkStatus::NetworkStatus(QObject *parent):QObject(parent)
{
    connect(&m_nNetWorkManager,SIGNAL(networkStatusChanged(bool, CNetworkManager::NetworkType)),
            this,  SLOT(slotNetworkStatusChanged(bool, CNetworkManager::NetworkType)));
    CNetworkManager::NetworkType type = m_nNetWorkManager.currentNetworkType();
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
}

void NetworkStatus::slotNetworkStatusChanged(bool flag, CNetworkManager::NetworkType type)
{
    Q_UNUSED(flag)
    if(type ==  CNetworkManager::Cellular)
        m_nConnectNetworkType = "cellular";
    else if(type == CNetworkManager::Wifi)
        m_nConnectNetworkType = "wifi";
    else
        m_nConnectNetworkType = "";
   emit networkConnectChanged(m_nConnectNetworkType);
}

QString NetworkStatus::getNetworkConnectStatus()
{
    return m_nConnectNetworkType;
}
