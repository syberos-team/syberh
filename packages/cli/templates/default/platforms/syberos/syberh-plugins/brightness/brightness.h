#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <QObject>
#include <QtPlugin>

#include "iplugin/iplugin.h"
#include "brightness_global.h"

class BRIGHTNESSSHARED_EXPORT Brightness : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Brightness();

    void invoke(QString callbackID, QString actionName, QVariantMap params);

private :

    /**
     * @brief maximumBrightness 获取系统屏幕亮度信息。
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数
     * @return 成功则返回系统屏幕亮度信息。
     *      失败则返回错误码。
     */
    void brightnessInfo(QString callbackID,QVariantMap params);

    /**
     * @brief setAdaptiveDimmingEnabled 设置自适应调光开关。
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数 true 使能该功能，false 关闭该功能
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void setAdaptiveDimmingEnabled(QString callbackID,QVariantMap params);

    /**
     * @brief setAmbientLightSensorEnabled 开关环境光感器。
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数 true 使能该功能，false 关闭该功能。
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void setAmbientLightSensorEnabled(QString callbackID,QVariantMap params);

    /**
     * @brief setBlankTimeout 设置息屏时长。
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数 要设置时长，单位秒。
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void setBlankTimeout(QString callbackID,QVariantMap params);

    /**
     * @brief setBrightness 设置屏幕亮度。
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数 要设置的亮度值。
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void setBrightness(QString callbackID,QVariantMap params);

    /**
     * @brief :setDimTimeout 设置无操作时屏幕进入暗屏状态的时长。
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数 设置要暗屏时长，单位秒。
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void setDimTimeout(QString callbackID,QVariantMap params);
};

#endif // BRIGHTNESS_H
