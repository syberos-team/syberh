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
#include "socketclient.h"
#include <QString>
#include <QObject>
#include <QDebug>


/**
 * 开发工具类
 * @brief The DevTools class
 */
class DevTools:public QObject
{
    Q_OBJECT
public:
    ~DevTools();
     static DevTools * getInstance();
private:
    DevTools();
    static DevTools *pDevTools;
    SocketClient *socketClient;
    //服务端IP
    QString serverIp();
    //服务端端口
    int serverPort();

public slots:
    void reload();
};

#endif // DEVTOOLS_H
