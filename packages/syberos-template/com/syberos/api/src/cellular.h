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

#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include "framework/nativesdkhandlerbase.h"
class Cellular : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Cellular();
    ~Cellular();

    void request(QString callBackID, QString actionName, QVariantMap params);

    void submit(QString typeID, QString callBackID, QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

private :

    /**
     * @brief aboutPhone 设置数据网络状态为关闭
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数
     * @return 设置成功返回 true
     * @return 设置失败返回 false
     */
    void  networkDisabled(long callBackID, QVariantMap params);

    /**
     * @brief aboutPhone 设置数据网络状态为启用
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数
     * @return 设置成功返回 true
     * @return 设置失败返回 false
     */
    void  networkEnabled(long callBackID, QVariantMap params);
};

#endif // NETWORKINFO_H
