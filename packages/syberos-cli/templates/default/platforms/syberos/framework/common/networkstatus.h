#ifndef NETWORKSTATUS_H
#define NETWORKSTATUS_H

#include <QObject>
#include <cnetworkmanager.h>
class NetworkStatus : public QObject
{
    Q_OBJECT
public:

    /**
     * 单例函数
     */
    static NetworkStatus *getInstance();

    /**
     * 析构函数
     */
    ~NetworkStatus();

    /**
     * @brief getNetworkConnectStatus : 网络链接状态
     * @return : "wifi":wlan； "cellular"：移动网络；"":无网络
     */
    Q_INVOKABLE QString getNetworkConnectStatus();

signals:
    /**
     * @brief networkConnectChanged : 网络链接状态变更信号
     * @param networkType : 网络链接状态
     */
    void networkConnectChanged(QString networkType);

public slots:
    /**
     * @brief slotNetworkStatusChanged : 网络链接状态变更槽函数
     * @param flag
     * @param type : 网络类型
     */
    void slotNetworkStatusChanged(bool flag, CNetworkManager::NetworkType type);

private:
    /**
     * 构造函数
     */
    NetworkStatus(QObject *parent = 0);
    static NetworkStatus *m_pNetworkStatus; ///<单例对象
    QString m_nConnectNetworkType; ///<链接网络类型
    CNetworkManager m_nNetWorkManager; ///<移动网络管理的对象
};

#endif // NETWORKSTATUS_H
