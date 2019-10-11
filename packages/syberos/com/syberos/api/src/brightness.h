/*
* This file is part of API
*
* Copyright (C) 2019 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:guohongfei
*
* author <guohongfei@syberos.com>
*
* This software, including documentation, is protected by  copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

#ifndef BRINGHTNESS_H
#define BRINGHTNESS_H

#include "framework/nativesdkhandlerbase.h"
class Brightness : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Brightness();
    ~Brightness();

    void request(QString callBackID, QString actionName, QVariantMap params);
    void submit(QString typeID, QString callBackID, QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

private :

    /**
     * @brief maximumBrightness 获取系统屏幕亮度信息。
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数
     * @return 成功则返回系统屏幕亮度信息。
     *      失败则返回错误码。
     */
    void brightnessInfo(long callBackID,QVariantMap params);

    /**
     * @brief setAdaptiveDimmingEnabled 设置自适应调光开关。
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数 true 使能该功能，false 关闭该功能
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void setAdaptiveDimmingEnabled(long callBackID,QVariantMap params);

    /**
     * @brief setAmbientLightSensorEnabled 开关环境光感器。
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数 true 使能该功能，false 关闭该功能。
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void setAmbientLightSensorEnabled(long callBackID,QVariantMap params);

    /**
     * @brief setBlankTimeout 设置息屏时长。
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数 要设置时长，单位秒。
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void setBlankTimeout(long callBackID,QVariantMap params);

    /**
     * @brief setBrightness 设置屏幕亮度。
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数 要设置的亮度值。
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void setBrightness(long callBackID,QVariantMap params);

    /**
     * @brief :setDimTimeout 设置无操作时屏幕进入暗屏状态的时长。
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数 设置要暗屏时长，单位秒。
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void setDimTimeout(long callBackID,QVariantMap params);

};

#endif // BRINGHTNESS_H
