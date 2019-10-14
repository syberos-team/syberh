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

#ifndef SYSTEM_H
#define SYSTEM_H

#include "framework/nativesdkhandlerbase.h"
class System : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE System();
    ~System();

    void request(QString callBackID, QString actionName, QVariantMap params);
    void submit(QString typeID, QString callBackID, QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

private :

    /**
     * @brief aboutPhone 获取手机信息
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void  aboutPhone(long callBackID,QVariantMap params);

    /**
     * @brief getResolution 获取手机分辨率
     * @param callBackID 获取手机分辨率的任务Id
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void  getResolution(long callBackID,QVariantMap params);

   /**
    * @brief getCoreVersion 获取内核版本号
    * @param callBackID 获取内核版本号的任务Id
    * @param params 参数
    * @return 成功则无返回。
    *      失败则返回错误码。
    */
   void  getCoreVersion(long callBackID,QVariantMap params);

   /**
    * @brief getSysVersionID 获取系统版本号
    * @param callBackID 获取内核版本号的任务Id
    * @param params 参数
    * @return 成功则无返回。
    *      失败则返回错误码。
    */
   void  getSysVersionID(long callBackID,QVariantMap params);

};

#endif // SYSTEMINFO_H
