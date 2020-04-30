#include <QDebug>
#include <QtPlugin>
#include "audio.h"
#include "framework/common/errorinfo.h"
#include "helper.h"

using namespace NativeSdk;


Audio::Audio(){
    player = new QMediaPlayer();
}

Audio::~Audio(){
    delete player;
}

void Audio::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    if(actionName == "start"){
        start(callbackID,params);
    }else if(actionName == "pause"){
        pause(callbackID,params);
    }else if(actionName == "resume"){
        resume(callbackID,params);
    }else if(actionName == "stop"){
        stop(callbackID,params);
    }
}

void Audio::start(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "start" << params << endl;

    QString filePath = params.value("path").toString();
    int position = params.value("position").toInt();

    qDebug() << Q_FUNC_INFO << "position" << position << endl;

    // 播放起始时间toInt以后和以前不一样，说明传入的不是正整数
    if (params.value("position") != "0" && position == 0) {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "不合法的参数:position必须是正整数");
        return;
    }

    if(filePath.isEmpty()){
        qDebug() << Q_FUNC_INFO << "文件路径不能为空" << endl;
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "不合法的参数:path不能为空");
        return;
    }

    QFile file(filePath);
    if(!file.exists()){
        qDebug() << Q_FUNC_INFO << "音频不存在：" << filePath << endl;
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidURLError, "无效的url:音频文件不存在");
        return;
    }

    bool ret = Helper::instance()->isAudio(filePath);
    if(!ret){
        qDebug() << Q_FUNC_INFO << "不是音频文件" << endl;
        signalManager()->failed(callbackID.toLong(), ErrorInfo::IllegalMediaTypeError, "不合法的媒体文件类型:不是音频文件");
        return;
    }

    player->setMedia(QUrl::fromLocalFile(filePath));
    player->setVolume(50);

    //有指定时间参数，从指定位置开始播放
    if(position != 0){
        player->setPosition(player->position() + (1000*position));
    }

    player->play();

    signalManager()->success(callbackID.toLong(), true);
}

void Audio::pause(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "pause" << params << endl;

    player->pause();
    signalManager()->success(callbackID.toLong(), true);
}

void Audio::resume(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "resume" << params << endl;

    int position = params.value("position").toInt();

    qDebug() << Q_FUNC_INFO << "position" << position << endl;

    // 播放起始时间toInt以后和以前不一样，说明传入的不是正整数
    if (params.value("position") != "0" && position == 0) {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "不合法的参数:position必须是正整数");
        return;
    }

    //有指定时间参数，从指定位置开始播放
    if(position != 0){
        player->stop();
        player->play();
        player->setPosition(player->position() + (1000*position));//从指定位置开始播放
    }else{
        player->play();
    }
    signalManager()->success(callbackID.toLong(), true);
}

void Audio::stop(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "stop" << params << endl;

    player->stop();
    signalManager()->success(callbackID.toLong(), true);
}

