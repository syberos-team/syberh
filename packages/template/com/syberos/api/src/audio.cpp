#include "audio.h"
#include "helper.h"

#include <QDebug>
#include <QUrlQuery>
#include <QException>
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

    if(actionName == "startPlay"){
        startPlay(params);
    }else if(actionName == "pausePlay"){
        pausePlay(params);
    }else if(actionName == "continuePlay"){
        continuePlay(params);
    }else if(actionName == "stopPlay"){
        stopPlay(params);
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

void Audio::startPlay(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "startPlay" << params << endl;
    QString filePath = params.value("path").toString();
    int position = params.value("position").toInt();

    player->setMedia(QUrl::fromLocalFile(filePath));
    player->setVolume(50);

    player->play();
    if(position != 0){
        player->setPosition(player->position() + (1000*position));//从指定位置开始播放
    }
}

void Audio::pausePlay(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "pausePlay" << params << endl;
    player->pause();
}

void Audio::continuePlay(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "continuePlay" << params << endl;

    int position = params.value("position").toInt();
    if(position != 0){
        player->stop();
        player->play();
        player->setPosition(player->position() + (1000*position));//从指定位置开始播放
    }else{
        player->play();
    }
}

void Audio::stopPlay(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "stopPlay" << params << endl;

    player->stop();
}
