#include "vibrator.h"
#include <QObject>
#include <QDebug>
#include "cngfmanager.h"
#include <QMediaPlayer>
#include <qjsonobject.h>
#include "csystemprofilemanager.h"
#include <QTimer>

int Vibrator::typeId = qRegisterMetaType<Vibrator *>();
Vibrator::Vibrator()
{
    // 创建CNGFManager的对象
    client = new CNgfManager(this);

    // 注册状态改变信号
    QObject::connect(client, SIGNAL(eventCompleted(quint32)), this, SLOT(eventCompleted(quint32)));
    QObject::connect(client, SIGNAL(eventFailed(quint32)), this, SLOT(eventFailed(quint32)));
    QObject::connect(client, SIGNAL(eventPlaying(quint32)), this, SLOT(eventPlaying(quint32)));

    profile = new CSystemProfileManager();
}
Vibrator::~Vibrator()
{
    // 断开信号连接
    QObject::disconnect(client, SIGNAL(eventCompleted(quint32)), this, SLOT(eventCompleted(quint32)));
    QObject::disconnect(client, SIGNAL(eventFailed(quint32)), this, SLOT(eventFailed(quint32)));
    QObject::disconnect(client, SIGNAL(eventPlaying(quint32)), this, SLOT(eventPlaying(quint32)));

    delete client;
    client = NULL;

    delete profile;
    profile = NULL;
}

void Vibrator::request(QString callBackID, QString actionName, QVariantMap params)
{
  if (actionName == "vibrate"){
    vibrate(callBackID.toLong(), params);
  }else if (actionName == "vibrateInfo"){
    vibrateInfo(callBackID.toLong(), params);
  }else if (actionName == "setTouchVibrationSoundEnabled"){
    setTouchVibrationSoundEnabled(callBackID.toLong(), params);
  }else if (actionName == "setVibratingEnabled"){
    setVibratingEnabled(callBackID.toLong(), params);
  }

}
void Vibrator::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
}

void Vibrator::vibrate(long callBackID, QVariantMap params){

    qDebug() << Q_FUNC_INFO << "params: " << params << endl;

    QString mode = params.value("mode").toString();
    qDebug() << Q_FUNC_INFO << "mode: " << mode << endl;
    qDebug() << Q_FUNC_INFO << "mode: mode.isEmpty() " << mode.isEmpty() << endl;
    qDebug() << Q_FUNC_INFO << "mode: short " << (QString::compare(mode, "short") != 0) << endl;
    qDebug() << Q_FUNC_INFO << "mode: long " << (QString::compare(mode, "long") != 0) << endl;

    if(mode.isEmpty()){
        emit failed(callBackID, ErrorInfo::InvalidParameter, "mode参数不能为空");
        return;
    }

    if(QString::compare(mode, "short") != 0
            && QString::compare(mode, "long") != 0){
        emit failed(callBackID, ErrorInfo::InvalidParameter, "mode参数不合法");
        return;
    }

    //打开震动开关
    bool vibratingEnabled = profile->vibratingEnabled();
    if(!vibratingEnabled){
        profile->setVibratingEnabled(true);
    }

    //连接震动服务
    bool isConnected = client->isConnected();
    if(!isConnected){
        isConnected = client->connect();
    }

    if(!isConnected){
        emit failed(callBackID, ErrorInfo::SystemError, "连接震动服务失败");
        return;
    }

    //长震400ms
    int vibratorTime = 400;
    if(mode == "short"){
        //长震15ms
        vibratorTime = 40;
    }

    qDebug() << Q_FUNC_INFO << "vibrate time: " << vibratorTime << endl;

    // 定义事件属性
    QMap<QString, QVariant> properties;
    properties.insert(QString("media.vibra"), QVariant(true));
    properties.insert(QString("vibrator.repeat"), QVariant(1));
    properties.insert(QString("vibrator.time"), QVariant(vibratorTime));

    quint32 event_id = client->play(CNgfManager::NgfVibrator, properties);
    qDebug() << Q_FUNC_INFO << "vibrate play eventId: " << event_id << endl;

    emit success(callBackID, "success");
}


void Vibrator::vibrateInfo(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO  << "callbackID is" << callBackID << "params is" << params << endl;

    CSystemProfileManager cspm;

    bool touch = cspm.touchVibrationSoundEnabled();
    bool vibrating = cspm.vibratingEnabled();

    QJsonObject json;
    json.insert("touch", touch);
    json.insert("vibrating", vibrating);

    qDebug() << Q_FUNC_INFO <<  QVariant(json)  << endl;
    emit success(callBackID,  json);
}

void Vibrator::setTouchVibrationSoundEnabled(long callBackID, QVariantMap params){
    qDebug() << Q_FUNC_INFO  << "callbackID is" << callBackID << "params is" << params << endl;

    bool enable = false;
    QString state = params.value("state").toString();
    if("0" == state){
        enable = false;
    }else if("1" == state){
        enable = true;
    }

    CSystemProfileManager cspm;

    cspm.setTouchVibrationSoundEnabled(enable);

    QJsonObject json;
    json.insert("result", true);

    qDebug() << Q_FUNC_INFO << json << endl;
    emit success(callBackID,  json);
}


void Vibrator::setVibratingEnabled(long callBackID,QVariantMap params){
    qDebug() << "setVibratingEnabled callbackID is" << callBackID << "params is" << params << endl;
    bool enable = false;
    QString state = params.value("state").toString();
    if("0" == state){
        enable = false;
    }else if("1" == state){
        enable = true;
    }

    CSystemProfileManager cspm;

    cspm.setVibratingEnabled(enable);

    QJsonObject json;
    json.insert("result", true);

    qDebug() << Q_FUNC_INFO << json << endl;
    emit success(callBackID,  json);
}

void Vibrator::eventFailed(quint32 eventId){
    qDebug() << Q_FUNC_INFO << "vibrate failed eventId: " << eventId;
}
void Vibrator::eventCompleted(quint32 eventId){
    qDebug() << Q_FUNC_INFO << "vibrate completed eventId: " << eventId;

    bool vibratingEnabled = profile->vibratingEnabled();
    if(vibratingEnabled){
        profile->setVibratingEnabled(false);
    }
}
void Vibrator::eventPlaying(quint32 eventId){
    qDebug() << Q_FUNC_INFO << "playing eventId: " << eventId << endl;
}
