#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include <QObject>
#include <QtPlugin>

#include "iplugin/iplugin.h"
#include "networkinfo_global.h"

class NETWORKINFOSHARED_EXPORT NetworkInfo: public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")


public:
    Q_INVOKABLE NetworkInfo();

    void invoke(QString callbackID, QString actionName, QVariantMap params);

private :

    /**
     * @brief aboutPhone 获取当前设备的网络信息
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数
     * @return 成功则返回当前设备的网络信息。
     * @return 失败则返回错误码。
     */
    void  info(QString callbackID, QVariantMap params);

};

#endif // NETWORKINFO_H
