/*
* This file is part of SocketClient
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
#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H
#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QBuffer>
#include <QIODevice>
#include <QDateTime>
#include <QFileInfo>
#include <QTimer>
#include "../../helper.h"
#include "devdownload.h"
#include "../../util/log.h"


/**
 * Socket客户端工具类
 * @brief The SocketClient class
 */
class SocketClient:public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE SocketClient(const QString &url, const int &port);
    ~SocketClient();
    static SocketClient *getInstance(const QString &url, const int &port);
    /**
     * @brief create 创建socket客户端
     * @param url IP地址
     * @param prot 端口
     */
    void create(const QString &url, const int &port);
    /**
     * @brief appendFile 保存内容到文件中
     * @param fqba 文件buffer
     */
    void appendFile(const QByteArray &fqba);
    QString purl;
    int pport;

signals:
    // 热更新完成
    void update();

public slots:

    void socketError(QAbstractSocket::SocketError error);
    void disconnected();
    void connection();
    void onProgress();
    void data();
    //下载完成信号
    void onReplyFinished(QString downloadId, QString path, int statusCode, QString errorMessage);


private:
    Log *log;
     QTimer *timer;
    //连接重试次数
    int connectCount;
    static SocketClient *pSocket;
    bool m_bServerConnected;
    Helper *helper;
    /**
     * @brief hotUpdate 热更新实现
     */
    void updateWebRoot();
    //需要下载的个数
    int total;

    int downloadTotal;

    /**
     * 获取临时目录地址,如果不存在则创建
     * @brief mkdirTemp
     * @return 临时文件路径
     */
    QString getOrCreateTempPath();


    /**
     * @brief initParams 初始化参数
     */
    void initParams();

    //临时目录
    QString tempPath;
    /**socket客户端*/
    QTcpSocket *socketClient;

    //保存文件的路径
    QString zfilePath;

    //传输ID
    int uid;
    // 文件名称
    QString fileName;
    //文件大小
    int fileSize;
    //已经发送进来的大小
    int hasSend;
    //临时目录名称
    QString TEMP_PATH_NAME;
};

#endif // SOCKETCLIENT_H
