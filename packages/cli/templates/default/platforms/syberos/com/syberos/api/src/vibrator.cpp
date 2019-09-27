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
    count=0;
}
Vibrator::~Vibrator()
{

}

void Vibrator::request(QString callBackID, QString actionName, QVariantMap params)
{
  if (actionName == "vibrate")
  {
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

void Vibrator::vibrate(long callBackID,QVariantMap params){

    qDebug() << Q_FUNC_INFO << "------params" << params << endl;


    // 创建CNGFManager的对象
    client = new CNgfManager(this);

    // 注册连接状态信号
    QObject::connect(client, SIGNAL(connectionStatusChanged(bool)), this, SLOT(connection(bool)));

    // 注册状态改变信号
    QObject::connect(client, SIGNAL(eventCompleted(quint32)), this, SLOT(completed(quint32)));
    QObject::connect(client, SIGNAL(eventFailed(quint32)), this, SLOT(failed(quint32)));
    QObject::connect(client, SIGNAL(eventPlaying(quint32)), this, SLOT(playing(quint32)));
bool b;
    // 连接到Ngf服务
    if (client->connect()) {

      // 定义事件属性
      QMap<QString, QVariant> properties;
      properties.insert(QString("media.vibra"), QVariant(true));

//    properties.insert(QString("vibrator.time"), QVariant(10000));
//    properties.insert(QString("media.vibra.force"), QVariant(true));
      properties.insert(QString("vibrator.repeat"), QVariant(false));

      // 开始播放并返回事件id
      quint32 event_id = client->play(CNgfManager::NgfVibrating, properties);

      qDebug() << Q_FUNC_INFO << "------eventId" << event_id << endl;
      b   =  client->stop(CNgfManager::NgfVibrating);
       qDebug() << Q_FUNC_INFO << "----stop:b" << b;
      QTimer::singleShot(300, this, SLOT(stop()));
     }

     QJsonObject json;
     json.insert("result", b );
     qDebug() << Q_FUNC_INFO << "----vibrate:b" << b;
     emit success(callBackID,  json);
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

void Vibrator::connection(bool connected){
    qDebug() << Q_FUNC_INFO << "connection" << connected;
}

void Vibrator::failed(quint32 eventId){
    qDebug() << Q_FUNC_INFO << "failed" << eventId;
}
void Vibrator::completed(quint32 eventId){
    qDebug() << Q_FUNC_INFO << "completed" << eventId;
    bool b   =  client->stop(eventId);
    qDebug() << Q_FUNC_INFO << "completed:b" << b;
}
void Vibrator::playing(quint32 eventId){
    qDebug() << Q_FUNC_INFO << "playing" << eventId << "count" << count;
    client->stop(CNgfManager::NgfVibrating);
//    if(count > 0){
//        qDebug() << Q_FUNC_INFO << "playing.........." << eventId << "count" << count;
//        client->stop(CNgfManager::NgfVibrating);
//    }
//    count++;
}
void Vibrator::stop(){
    qDebug() << Q_FUNC_INFO << "stop";
    bool b   =  client->stop(CNgfManager::NgfVibrating);
    qDebug() << Q_FUNC_INFO << "stop:b" << b;
}
