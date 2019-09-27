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
        start(callBackID.toLong(),params);
    }else if(actionName == "pause"){
        pause(callBackID.toLong(),params);
    }else if(actionName == "resume"){
        resume(callBackID.toLong(),params);
    }else if(actionName == "stop"){
        stop(callBackID.toLong(),params);
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

void Audio::start(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "start" << params << endl;

    QString filePath = params.value("path").toString();
    int position = params.value("position").toInt();

    if(filePath.isEmpty()){
        qDebug() << Q_FUNC_INFO << "文件路径不能为空" << endl;
        emit failed(callBackID, 500, "文件路径不能为空");
        return;
    }

    QFile file(filePath);
    if(!file.exists()){
        qDebug() << Q_FUNC_INFO << "音频不存在：" << filePath << endl;
        emit failed(callBackID, 500, "音频不存在");
        return;
    }

    bool ret = Helper::instance()->isAudio(filePath);
    if(!ret){
        qDebug() << Q_FUNC_INFO << "不是音频文件" << endl;
        emit failed(callBackID, 500, "不是音频文件");
        return;
    }

    player->setMedia(QUrl::fromLocalFile(filePath));
    player->setVolume(50);
    player->play();

    //有指定时间参数，从指定位置开始播放
    if(position != 0){
        player->setPosition(player->position() + (1000*position));
    }
    emit success(callBackID, true);
}

void Audio::pause(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "pause" << params << endl;

    player->pause();
    emit success(callBackID, true);
}

void Audio::resume(long callBackID,QVariantMap params){
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
    emit success(callBackID, true);
}

void Audio::stop(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "stop" << params << endl;

    player->stop();
    emit success(callBackID, true);
}
