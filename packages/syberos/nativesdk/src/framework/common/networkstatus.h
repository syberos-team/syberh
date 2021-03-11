#ifndef NETWORKSTATUS_H
#define NETWORKSTATUS_H

#include <QObject>
#include <QScopedPointer>

#include "../../nativesdk_global.h"

QT_BEGIN_NAMESPACE
class CNetworkManager;
QT_END_NAMESPACE

namespace NativeSdk {

class NATIVESDK_EXPORT NetworkStatus : public QObject
{
    Q_OBJECT
public:
    enum NetworkType {
        None,
        Wifi,
        Cellular,
        Ethernet
    };

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
     * @return : "wifi":wlan； "cellular"：移动网络； "ethernet":以太网；"":无网络
     */
    Q_INVOKABLE QString getNetworkConnectStatus();

    Q_INVOKABLE NetworkType getNetworkConnectType();

signals:
    /**
     * @brief networkConnectChanged : 网络链接状态变更信号
     * @param networkType : 网络链接状态
     */
    void networkConnectChanged(NetworkType networkType);

public slots:
    /**
     * @brief slotNetworkStatusChanged : 网络链接状态变更槽函数
     * @param flag
     * @param type : 网络类型
     */
    void slotNetworkStatusChanged(bool flag, NetworkType type);

private:
    /**
     * 构造函数
     */
    NetworkStatus(QObject *parent = 0);
    static NetworkStatus *m_networkStatus; ///<单例对象
    CNetworkManager *m_newworkManager = NULL;  ///<移动网络管理的对象
    NetworkType m_networkType = None;
};
}
#endif // NETWORKSTATUS_H
