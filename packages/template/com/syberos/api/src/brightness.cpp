#include "brightness.h"
#include <QObject>
#include <QDebug>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <cdisplaysettings.h>



int Brightness::typeId = qRegisterMetaType<Brightness *>();
Brightness::Brightness()
{

}
Brightness::~Brightness()
{

}

void Brightness::request(QString callBackID, QString actionName, QVariantMap params)
{
    Q_UNUSED(actionName);
    Q_UNUSED(params);

    //如果参数不使用此方法可以防止运行异常
    Q_UNUSED(params);
    if (actionName=="brightnessInfo"){
        brightnessInfo(callBackID.toLong(), params);
    }else if (actionName=="setAdaptiveDimmingEnabled"){
        setAdaptiveDimmingEnabled(callBackID.toLong(), params);
    }else if (actionName=="setAmbientLightSensorEnabled"){
        setAmbientLightSensorEnabled(callBackID.toLong(), params);
    }else if (actionName=="setBlankTimeout"){
        setBlankTimeout(callBackID.toLong(), params);
    }else if (actionName=="setBrightness"){
        setBrightness(callBackID.toLong(), params);
    }else if (actionName=="setDimTimeout"){
        setDimTimeout(callBackID.toLong(), params);
    }

}

void Brightness::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID);
    Q_UNUSED(callBackID);
    Q_UNUSED(actionName);
    Q_UNUSED(dataRowList);
    Q_UNUSED(attachementes);

}

void Brightness::brightnessInfo(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "callBackID" << callBackID << ", params" << params << endl;
    CSystemDisplaySettings display;

    int max = display.maximumBrightness();
    bool adaptiveDimmingEnabled = display.adaptiveDimmingEnabled();
    bool ambientLightSensorEnabled = display.ambientLightSensorEnabled();

    int blankTime = display.blankTimeout();
    int brightness = display.brightness();
    int dimTimeout = display.dimTimeout();

    QJsonObject json;
    json.insert("maximumBrightness", max);
    json.insert("blankTime", blankTime);
    json.insert("brightness", brightness);
    json.insert("dimTimeout", dimTimeout);
    json.insert("ambientLightSensorEnabled", ambientLightSensorEnabled);
    json.insert("adaptiveDimmingEnabled", adaptiveDimmingEnabled);

    qDebug() << Q_FUNC_INFO << "json:" << json << endl;

    emit success(callBackID,  json);
}

void Brightness::setAdaptiveDimmingEnabled(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "callBackID" << callBackID << ", params" << params << endl;

    QString state = params.value("state").toString();
    bool enable = false;
    if("0" == state){
        enable = false;
    }else if("1" == state){
        enable = true;
    }

    CSystemDisplaySettings display;

    display.setAdaptiveDimmingEnabled(enable);

    qDebug() << "setAdaptiveDimmingEnabled: " << enable << endl;
    QJsonObject json;
    json.insert("result", true);
    qDebug() << Q_FUNC_INFO << "json:" << json << endl;
    emit success(callBackID,  json);
}

void Brightness::setAmbientLightSensorEnabled(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "callBackID" << callBackID << ", params" << params << endl;

    QString state = params.value("state").toString();
    bool enable;
    if("0" == state){
        enable = false;
    }else if("1" == state){
        enable = true;
    }

    CSystemDisplaySettings display;

    display.setAmbientLightSensorEnabled(enable);

    qDebug() << "setAmbientLightSensorEnabled: " << enable << endl;
    QJsonObject json;
    json.insert("result", true);
    qDebug() << Q_FUNC_INFO << "json:" << json << endl;
    emit success(callBackID,  json);
}

void Brightness::setBlankTimeout(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "callBackID" << callBackID << ", params" << params << endl;

    int timeout = params.value("timeout").toInt();

    CSystemDisplaySettings display;

    display.setBlankTimeout(timeout);

    qDebug() << "setBlankTimeout: " << timeout << endl;
    QJsonObject json;
    json.insert("result", true);
    qDebug() << Q_FUNC_INFO << "json:" << json << endl;
    emit success(callBackID,  json);
}

void Brightness::setBrightness(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "callBackID" << callBackID << ", params" << params << endl;
    bool ok;
    int brightness = params.value("brightness").toString().toInt(&ok, 10);

    CSystemDisplaySettings display;

    display.setBrightness(brightness);

    qDebug() << "setBrightness: " << brightness << endl;
    QJsonObject json;
    json.insert("result", true);
    qDebug() << Q_FUNC_INFO << "json:" << json << endl;
    emit success(callBackID,  json);
}

void Brightness::setDimTimeout(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "callBackID" << callBackID << ", params" << params << endl;

    int timeout = params.value("timeout").toInt();

    CSystemDisplaySettings display;

    display.setDimTimeout(timeout);

    qDebug() << "setDimTimeout: " << timeout << endl;
    QJsonObject json;
    json.insert("result", true);
    qDebug() << Q_FUNC_INFO << "json:" << json << endl;
    emit success(callBackID,  json);
}
