#include <QDebug>
#include <QDebug>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <cdisplaysettings.h>

#include "brightness.h"


Brightness::Brightness()
{
}


void Brightness::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    if (actionName=="brightnessInfo"){
        brightnessInfo(callbackID, params);
    }else if (actionName=="setAdaptiveDimmingEnabled"){
        setAdaptiveDimmingEnabled(callbackID, params);
    }else if (actionName=="setAmbientLightSensorEnabled"){
        setAmbientLightSensorEnabled(callbackID, params);
    }else if (actionName=="setBlankTimeout"){
        setBlankTimeout(callbackID, params);
    }else if (actionName=="setBrightness"){
        setBrightness(callbackID, params);
    }else if (actionName=="setDimTimeout"){
        setDimTimeout(callbackID, params);
    }
}


void Brightness::brightnessInfo(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "callbackID" << callbackID << ", params" << params << endl;
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

    signalManager()->success(callbackID.toLong(), json);
}

void Brightness::setAdaptiveDimmingEnabled(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "callbackID" << callbackID << ", params" << params << endl;

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
    signalManager()->success(callbackID.toLong(), json);
}

void Brightness::setAmbientLightSensorEnabled(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "callbackID" << callbackID << ", params" << params << endl;

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
    signalManager()->success(callbackID.toLong(), json);
}

void Brightness::setBlankTimeout(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "callbackID" << callbackID << ", params" << params << endl;

    int timeout = params.value("timeout").toInt();

    CSystemDisplaySettings display;

    display.setBlankTimeout(timeout);

    qDebug() << "setBlankTimeout: " << timeout << endl;
    QJsonObject json;
    json.insert("result", true);
    qDebug() << Q_FUNC_INFO << "json:" << json << endl;
    signalManager()->success(callbackID.toLong(), json);
}

void Brightness::setBrightness(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "callbackID" << callbackID << ", params" << params << endl;
    bool ok;
    int brightness = params.value("brightness").toString().toInt(&ok, 10);

    CSystemDisplaySettings display;

    display.setBrightness(brightness);

    qDebug() << "setBrightness: " << brightness << endl;
    QJsonObject json;
    json.insert("result", true);
    qDebug() << Q_FUNC_INFO << "json:" << json << endl;
    signalManager()->success(callbackID.toLong(), json);
}

void Brightness::setDimTimeout(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "callbackID" << callbackID << ", params" << params << endl;

    int timeout = params.value("timeout").toInt();

    CSystemDisplaySettings display;

    display.setDimTimeout(timeout);

    qDebug() << "setDimTimeout: " << timeout << endl;
    QJsonObject json;
    json.insert("result", true);
    qDebug() << Q_FUNC_INFO << "json:" << json << endl;
    signalManager()->success(callbackID.toLong(), json);
}

