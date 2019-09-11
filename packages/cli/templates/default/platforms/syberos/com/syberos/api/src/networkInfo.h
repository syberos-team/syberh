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
class NetworkInfo : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE NetworkInfo();
    ~NetworkInfo();

    void request(QString callBackID, QString actionName, QVariantMap params);

    void submit(QString typeID, QString callBackID, QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

private :

    /**
     * @brief aboutPhone 获取当前设备的网络信息
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数
     * @return 成功则返回当前设备的网络信息。
     * @return 失败则返回错误码。
     */
    void  info(long callBackID, QVariantMap params);
};

#endif // NETWORKINFO_H
