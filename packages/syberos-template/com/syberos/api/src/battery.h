/*
* This file is part of DevTools
*
* Copyright (C) 2019 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:liguanghui
*
* author <liguanghui@syberos.com>
*
* This software, including documentation, is protected by  copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

#ifndef BATTERY_H
#define BATTERY_H

#include "framework/nativesdkhandlerbase.h"
class Battery : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Battery();
    ~Battery();

    void request(QString callBackID, QString actionName, QVariantMap params);

    void submit(QString typeID, QString callBackID, QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

private :

    /**
     * @brief aboutPhone 获取当前设备的电量信息
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数
     * @return 成功则返回当前设备的电量信息及是否在充电。
     * @return 失败则返回错误码。
     */
    void  getStatus(long callBackID, QVariantMap params);
};

#endif // SYSTEMINFO_H
