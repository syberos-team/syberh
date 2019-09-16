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
    player = new QMediaPlayer;
    recoder = new QAudioRecorder();
    playlist = new QMediaPlaylist;
//    mediaContent = new QMediaContent();
//    mediaResource = new QMediaResource();
}

Audio::~Audio(){
    delete player;
    delete recoder;
}

void Audio::request(QString callBackID, QString actionName, QVariantMap params)
{
    if (actionName == "listRecorder"){
        listRecorder(callBackID.toLong(), params);
    }else if (actionName == "startRecorder"){
        startRecorder(callBackID.toLong(), params);
    }else if(actionName == "stopRecorder"){
        stopRecorder(params);
    }else if(actionName == "startPlay"){
        startPlay(params);
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

void Audio::listRecorder(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "listRecorder" << params << endl;

    QString path = Helper::instance()->getInnerStorageRootPath() + "/audio";
    QFileInfoList fileInfos = FileUtil::fileList(path);
    QJsonArray jsonArr;
    if (fileInfos.size() != 0) {
        for (int i = 0; i < fileInfos.size(); i++) {
            QJsonObject jsonObj;
            jsonObj.insert("path", fileInfos.at(i).filePath());
            jsonObj.insert("size", fileInfos.at(i).size());
            jsonObj.insert("created", fileInfos.at(i).created().toString("yyyy-MM-dd hh:mm:ss"));

            qint64 time = fileInfos.at(i).size() / (16000.0 * 2.0);    //总时长
            qDebug() << Q_FUNC_INFO << "time" << time << endl;

            jsonObj.insert("time", time);
            jsonArr.append(jsonObj);
        }

    }

    emit success(callBackID, jsonArr);
}

void Audio::startRecorder(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "startRecorder" << params << endl;

    QAudioEncoderSettings audioSettings;	//通过QAudioEncoderSettings类进行音频编码设置
    audioSettings.setCodec("audio/AAC");
    audioSettings.setSampleRate(16000);
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

    QJsonObject jsonObject;
    jsonObject.insert("path", newFile);

    QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);
    qDebug() << Q_FUNC_INFO << "recPath: " << jsonObjectValue.toString() << endl;

    emit success(callBackID, QVariant(jsonObject));
}

void Audio::stopRecorder(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "stopRecorder" << params << endl;

    recoder->stop();
}

void Audio::startPlay(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "startPlay" << params << endl;
    QString filePath = params.value("path").toString();

    player->setMedia(QUrl::fromLocalFile(filePath));
    player->setVolume(50);
    player->play();
}

void Audio::stopPlay(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "stopPlay" << params << endl;

    player->stop();
}
