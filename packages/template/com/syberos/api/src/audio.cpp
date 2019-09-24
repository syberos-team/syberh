#include "audio.h"
#include "helper.h"

#include <QDebug>
#include <QUrlQuery>
#include <QQuickView>
#include <QMetaObject>
#include <QGuiApplication>
#include "util/fileutil.h"

int Audio::typeId = qRegisterMetaType<Audio *>();

Audio::Audio(){
    player = new QMediaPlayer();
}

Audio::~Audio(){
    delete player;
}

void Audio::request(QString callBackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "request" << callBackID << endl;

    if(actionName == "start"){
        start(params);
    }else if(actionName == "pause"){
        pause(params);
    }else if(actionName == "resume"){
        resume(params);
    }else if(actionName == "stop"){
        stop(params);
    }
}

void Audio::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
}

void Audio::start(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "start" << params << endl;

    QString filePath = params.value("path").toString();
    int position = params.value("position").toInt();

    player->setMedia(QUrl::fromLocalFile(filePath));
    player->setVolume(50);
    player->play();

    //有指定时间参数，从指定位置开始播放
    if(position != 0){
        player->setPosition(player->position() + (1000*position));
    }
}

void Audio::pause(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "pause" << params << endl;

    player->pause();
}

void Audio::resume(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "resume" << params << endl;

    int position = params.value("position").toInt();

    //有指定时间参数，从指定位置开始播放
    if(position != 0){
        player->stop();
        player->play();
        player->setPosition(player->position() + (1000*position));//从指定位置开始播放
    }else{
        player->play();
    }
}

void Audio::stop(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "stop" << params << endl;

    player->stop();
}
