#include "system.h"
#include <QObject>
#include <QDebug>
#include <cosinfo.h>
#include <csystemdeviceinfo.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <qscreen.h>
#include <qguiapplication.h>

int System::typeId = qRegisterMetaType<System *>();
System::System()
{

}
System::~System()
{

}

void System::request(QString callBackID, QString actionName, QVariantMap params)
{
  if (actionName == "getCoreVersion")
  {
    getCoreVersion(callBackID.toLong(), params);
  }else if(actionName == "aboutPhone"){
    aboutPhone(callBackID.toLong(), params);
  }else if(actionName == "getResolution"){
    getResolution(callBackID.toLong(), params);
  }else if(actionName == "getSysVersionID"){
    getSysVersionID(callBackID.toLong(), params);
  }

}
void System::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{

}

void System::aboutPhone(long callBackID,QVariantMap params){
    int modem = 0;
    QVariant modemObj = params.value("modem");
    if(!modemObj.isNull() && !modemObj.isValid()){
        modem = modemObj.toInt();
    }
    CSystemDeviceInfo deviceInfo;

    QJsonValue id = QJsonValue::fromVariant(deviceInfo.uniqueDeviceId());
    QJsonValue name = QJsonValue::fromVariant(deviceInfo.productName());
    QJsonValue imei = QJsonValue::fromVariant(deviceInfo.imei(modem));
    QJsonArray simcardNumberJsonArr = QJsonArray::fromStringList(deviceInfo.simcardNumber());
    QJsonValue sincardNumberJsonValue = QJsonValue::fromVariant(simcardNumberJsonArr);

    QJsonArray imsisJsonArr = QJsonArray::fromStringList(deviceInfo.imsis());
    QJsonValue imsisJsonValue = QJsonValue::fromVariant(imsisJsonArr);

    QJsonObject jsonObject;
    jsonObject.insert("id", id);
    jsonObject.insert("name", name);
    jsonObject.insert("imei", imei);
    jsonObject.insert("simcardNumber", sincardNumberJsonValue);
    jsonObject.insert("imsis", imsisJsonValue);

    QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);
    qDebug() << "aboutPhone: " << jsonObjectValue.toString() << endl;
    emit success(callBackID, QVariant(jsonObject));
}

void System::getResolution(long callBackID,QVariantMap params){

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect mm = screen->availableGeometry() ;
    int width = mm.width();
    int height = mm.height();

    QJsonObject screenObj;
    screenObj.insert("width", width);
    screenObj.insert("height", height);

    qDebug() << "getResolution, width:" << width << ", height: " << height << endl;
    emit success(callBackID, QVariant(screenObj));
}

void System::getCoreVersion(long callBackID,QVariantMap params){
    COsInfo info;
    QString version = info.kernelVersion();
    qDebug() << "getCoreVersion: " << version << endl;
    emit success(callBackID, QVariant(version));
}

void System::getSysVersionID(long callBackID,QVariantMap params){
    COsInfo info;
    QString version = info.osVersion();
    qDebug() << "getSysVersionID: " << version << endl;
    emit success(callBackID, QVariant(version));
}
