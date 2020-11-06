/*
* This file is part of DevTools
*
* Copyright (C) 2019 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:lihejia
*
* author <lihejia@syberos.com>
*
* This software, including documentation, is protected by  copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

#ifndef DEVTOOLS_H
#define DEVTOOLS_H
#include <QString>
#include <QObject>
#include <QDebug>
#include "../nativesdkhandlerbase.h"
#include "socketclient.h"

/**
 * 开发工具类
 * @brief The DevTools class
 */
class DevTools:public NativeSdk::NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE DevTools();
    ~DevTools();
    static DevTools *getInstance();
    void request(QString callBackID,QString actionName,QVariantMap params);
    static int typeId;
private:
    static DevTools *pDevTools;
    SocketClient *socketClient;
    //服务端IP
    QString serverIp();
    //服务端端口
    int serverPort();
    /**
     * @brief 拷贝临时目录
     * @return
     */
    bool copyWWW();

public slots:
    void reload();
};

#endif // DEVTOOLS_H
