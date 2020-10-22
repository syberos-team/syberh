#ifndef BATTERY_H
#define BATTERY_H

#include <QObject>
#include <QtPlugin>

#include "iplugin/iplugin.h"
#include "battery_global.h"

class BATTERYSHARED_EXPORT Battery : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Battery();

    void invoke(QString callbackID, QString actionName, QVariantMap params);

private :
    /**
     * @brief aboutPhone 获取当前设备的电量信息
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数
     * @return 成功则返回当前设备的电量信息及是否在充电。
     * @return 失败则返回错误码。
     */
    void  getStatus(QString callbackID, QVariantMap params);
};

#endif // BATTERY_H
