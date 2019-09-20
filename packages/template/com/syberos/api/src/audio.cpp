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
    recoder = new QAudioRecorder();
    historydata = new HistoryData();
}

Audio::~Audio(){
    delete player;
    delete recoder;
}

void Audio::request(QString callBackID, QString actionName, QVariantMap params)
{
    if (actionName == "recorderList"){
        recorderList(callBackID.toLong(), params);
    }else if (actionName == "startRecorder"){
        startRecorder(callBackID.toLong(), params);
    }else if (actionName == "pauseRecorder"){
        pauseRecorder(params);
    }else if (actionName == "continueRecorder"){
        continueRecorder(params);
    }else if(actionName == "stopRecorder"){
        stopRecorder(params);
    }else if(actionName == "delRecorder"){
        delRecorder(callBackID.toLong(),params);
    }else if(actionName == "startPlay"){
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

void Audio::recorderList(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "recorderList" << params << endl;

//    QString path = Helper::instance()->getInnerStorageRootPath() + "/audio";
//    QFileInfoList fileInfos = FileUtil::fileList(path);// 获取录音文件目录下所有文件
//    QJsonArray jsonArr;

//    if (fileInfos.size() != 0) {
//        for (int i = 0; i < fileInfos.size(); i++) {

//            QString filePath = fileInfos.at(i).filePath();
//            qDebug() << Q_FUNC_INFO << "filePath" << filePath << endl;

//            if(filePath.right(4) == ".aac"){//过滤掉非.acc录音文件
//                QJsonObject jsonObj;
//                jsonObj.insert("path", filePath);
//                jsonObj.insert("size", fileInfos.at(i).size());
//                jsonObj.insert("created", fileInfos.at(i).created().toString("yyyy-MM-dd hh:mm:ss"));

//                qint64 time = fileInfos.at(i).size() / (16000.0 * 2.0);    //总时长
//                jsonObj.insert("time", time);
//                jsonArr.append(jsonObj);
//            }
//        }
//    }

//    emit success(callBackID, jsonArr);

    //从数据库中获取录音列表
    QJsonArray jsonArr;
    try  {
        jsonArr = historydata->selectMetadata();
    } catch (QException e) {
        emit failed(callBackID, 500, "查询录音列表失败");
    }

    emit success(callBackID, jsonArr);
}

void Audio::delRecorder(long callBackID, QVariantMap params){
    qDebug() << Q_FUNC_INFO << "delRecorder" << params << endl;
    QString filePath = params.value("path").toString();

    try  {
        //删除本机记录
        FileUtil::remove(filePath,0);
        //删除数据库中记录
        historydata->removeMetadata(filePath);
    } catch (QException e) {
        emit failed(callBackID, 500, "删除录音失败");
    }

    QJsonObject jsonObject;
    jsonObject.insert("result", true);
    emit success(callBackID, jsonObject);
}

void Audio::startRecorder(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "startRecorder" << params << endl;

    QAudioEncoderSettings audioSettings;	//通过QAudioEncoderSettings类进行音频编码设置
    audioSettings.setCodec("audio/AAC");    //编码
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
    qDebug() << Q_FUNC_INFO << "recPath" << jsonObjectValue.toString() << endl;

    //在数据库中添加录音记录，文件大小、总时长默认0
    historydata->insertMetadata(newFile,0,0,time.toString("yyyy-MM-dd hh:mm:ss"));
    currPath = newFile;

    emit success(callBackID, QVariant(jsonObject));
}

void Audio::pauseRecorder(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "pauseRecorder" << params << endl;
    recoder->pause();
}

void Audio::continueRecorder(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "continueRecorder" << params << endl;

    recoder->record();
}

void Audio::stopRecorder(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "stopRecorder" << params << endl;

    recoder->stop();

    //在数据库中修改录音记录，增加文件大小、总时长
    FileInfo fileInfo = FileUtil::getInfo(currPath);
    historydata->updateMetadata(currPath,fileInfo.size,recoder->duration());
}

void Audio::startPlay(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "startPlay" << params << endl;
    QString filePath = params.value("path").toString();

    player->setMedia(QUrl::fromLocalFile(filePath));
    player->setVolume(50);
    player->play();
}

void Audio::pausePlay(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "pausePlay" << params << endl;
    player->pause();
}

void Audio::continuePlay(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "continuePlay" << params << endl;
    player->play();
}

void Audio::stopPlay(QVariantMap params){
    qDebug() << Q_FUNC_INFO << "stopPlay" << params << endl;

    player->stop();
}
