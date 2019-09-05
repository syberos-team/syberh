#include "audio.h"
#include "helper.h"

#include <QDebug>
#include <QUrlQuery>
#include <QQuickView>
#include <QMetaObject>
#include <QGuiApplication>

int Audio::typeId = qRegisterMetaType<Audio *>();

Audio::Audio(){
    player = new QMediaPlayer;
    recoder = new QAudioRecorder();
    playlist = new QMediaPlaylist;
}

Audio::~Audio(){
    delete player;
    delete recoder;
}

void Audio::request(QString callBackID, QString actionName, QVariantMap params)
{
  if (actionName == "startAudioRecorder"){
      startAudioRecorder(callBackID.toLong(), params);
  }else if(actionName == "stopAudioRecorder"){
      stopAudioRecorder(params);
  }else if(actionName == "startAudioPlay"){
      startAudioPlay(params);
  }else if(actionName == "stopAudioPlay"){
      stopAudioPlay(params);
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

void Audio::startAudioRecorder(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "startAudioRecorder" << params << endl;

    QAudioEncoderSettings audioSettings;	//通过QAudioEncoderSettings类进行音频编码设置
    audioSettings.setCodec("audio/AAC");
    audioSettings.setQuality(QMultimedia::HighQuality);
    recoder->setAudioSettings(audioSettings);

    //获取用户文件存储地址
    QString path = Helper::instance()->getInnerStorageRootPath() + "/audio";
    QDir dir(path);
    if(!dir.exists()){
        dir.mkpath(path);
    }
    //配置保存的路径及文件名
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int timeT = time.toTime_t();                     //将当前时间转为时间戳
    QString timeStr = time.toString("yyyyMMdd");

    QString newFile = path + "/" +  timeStr + "_" + QString::number(timeT) + ".aac";
    QFile file(newFile);

    if(file.open(QFile::WriteOnly)){
        file.setPermissions(QFileDevice::ReadOwner|QFileDevice::WriteOwner|QFileDevice::ReadUser);
        file.close();
        recoder->setOutputLocation(QUrl(file.fileName()));	//设置保存的路径及文件名
        recoder->record();
    }

//    playlist = new QMediaPlaylist;
//    playlist->addMedia(QUrl(newFile));

    QJsonObject jsonObject;
    jsonObject.insert("path", newFile);

    QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);
    qDebug() << Q_FUNC_INFO << "recPath: " << jsonObjectValue.toString() << endl;

    emit success(callBackID, QVariant(jsonObject));
}

void Audio::stopAudioRecorder(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "stopAudioRecorder" << params << endl;

    recoder->stop();
}

void Audio::startAudioPlay(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "startAudioPlay" << params << endl;
    QString filePath = params.value("path").toString();

    player->setMedia(QUrl::fromLocalFile(filePath));
    player->setVolume(50);
    player->play();
}

void Audio::stopAudioPlay(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "stopAudioPlay" << params << endl;

    player->stop();
}
