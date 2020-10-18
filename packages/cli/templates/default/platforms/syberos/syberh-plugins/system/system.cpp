#include "system.h"
#include <QDebug>
#include <cosinfo.h>
#include <csystemdeviceinfo.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <qscreen.h>
#include <qguiapplication.h>
#include <QSize>
#include <QTimeZone>
#include <QLocale>
#include <QDateTime>
#include <ctime.h>
#include <QDBusConnection>
#include <QDBusMessage>



static const QString COMPOSITOR_SERVICE_NAME = "com.syberos.compositor";
static const QString COMPOSITOR_OBJECT_PATH = "/com/syberos/compositor";
static const QString COMPOSITOR_INTERFACE_NAME = "com.syberos.compositor.CompositorInterface";

System::System()
{
}


void System::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    Q_UNUSED(actionName);

    if (actionName == "aboutPhone") {
        aboutPhone(callbackID, params);
    }

     if (actionName == "setDate") {
        setDate(callbackID, params);
    }
}


void System::aboutPhone(QString callbackID,QVariantMap params){
    Q_UNUSED(callbackID);
    Q_UNUSED(params);
    int modem = 0;

    qDebug() << Q_FUNC_INFO << "callbackID:" << callbackID << ", params: " << params << endl;

    CSystemDeviceInfo deviceInfo;
    QJsonValue deviceId = QJsonValue::fromVariant(deviceInfo.uniqueDeviceId());
    QJsonValue name = QJsonValue::fromVariant(deviceInfo.productName());
    QJsonValue imei = QJsonValue::fromVariant(deviceInfo.imei(modem));
    QJsonArray simcardNumberJsonArr = QJsonArray::fromStringList(deviceInfo.simcardNumber());
    QJsonArray imsisJsonArr = QJsonArray::fromStringList(deviceInfo.imsis());
    COsInfo info;
    QJsonValue kernelVersion = QJsonValue::fromVariant(info.kernelVersion());
    QJsonValue osVersion = QJsonValue::fromVariant(info.osVersion());
    QJsonValue osVersionCode = QJsonValue::fromVariant(info.osVersionCode());
    QJsonValue softwareVersion = QJsonValue::fromVariant(info.softwareVersion());
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect mm = screen->availableGeometry() ;
    int screenWidth = mm.width();
    int screenHeight = mm.height();
    qreal pixelRatio = screen->devicePixelRatio();//设备像素比
    QLocale locale;
    QJsonValue language = QJsonValue::fromVariant(QLocale::languageToString(locale.language()));//获取系统语言
    QJsonValue region = locale.countryToString(locale.country());//获取系统地区

    QJsonObject jsonObject;
    jsonObject.insert("deviceId", deviceId);
    jsonObject.insert("brand", "");//设备品牌
    jsonObject.insert("manufacturer", "");//设备生产商
    jsonObject.insert("model", "");//设备型号
    jsonObject.insert("name", name);//手机名称
    jsonObject.insert("imei", imei);//移动设备国际识别码
    jsonObject.insert("simCardNumbers", simcardNumberJsonArr);//如果是双卡，有多个手机号
    jsonObject.insert("imsis", imsisJsonArr);//如果是双卡，有多个国际移动用户识别码
    jsonObject.insert("osType", "Syber");//操作系统名称
    jsonObject.insert("osVersionName", softwareVersion);//操作系统版本名称
    jsonObject.insert("osVersion", osVersion);//操作系统版本号
    jsonObject.insert("osVersionCode", osVersionCode);//操作系统小版本号
    jsonObject.insert("platformVersionName", "");//运行平台版本名称
    jsonObject.insert("platformVersionCode", "");//运行平台版本号
    jsonObject.insert("kernelVersion", kernelVersion);//内核版本号
    jsonObject.insert("screenWidth", screenWidth);//屏幕宽
    jsonObject.insert("screenHeight", screenHeight);//屏幕高
    jsonObject.insert("windowWidth", "");//可使用窗口宽度
    jsonObject.insert("windowHeight", "");//可使用窗口高度
    jsonObject.insert("statusBarHeight", "");//状态栏的高度 （待实现）
    jsonObject.insert("pixelRatio", pixelRatio);//设备像素比
    jsonObject.insert("language", language);//系统语言
    jsonObject.insert("region", region);//系统地区

    QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);

    qDebug() << Q_FUNC_INFO << "jsonObject:" << jsonObject << ", jsonObjectValue: " << jsonObjectValue << endl;

    signalManager()->success(callbackID.toLong(), QVariant(jsonObject));
}


void System::setVirtualPanel(QString callbackID,QVariantMap params){
    Q_UNUSED(callbackID);
    Q_UNUSED(params);

    qDebug() << Q_FUNC_INFO << "callbackID:" << callbackID << ", params: " << params << endl;
    
    bool visible= params.value("visible").toBool();
    QDBusMessage dbusMessage = QDBusMessage::createMethodCall(COMPOSITOR_SERVICE_NAME,
                                                              COMPOSITOR_OBJECT_PATH,
                                                              COMPOSITOR_INTERFACE_NAME,
                                                              "setVirtualPanelVisible");
    dbusMessage << visible;
    qDebug() << QDBusConnection::systemBus().send(dbusMessage);



    QJsonObject jsonObject;
    jsonObject.insert("visible", visible);
   
    
    QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);

    qDebug() << Q_FUNC_INFO << "jsonObject:" << jsonObject << ", jsonObjectValue: " << jsonObjectValue << endl;

    signalManager()->success(callbackID.toLong(), QVariant(jsonObject));
}


void System::setDate(QString callbackID,QVariantMap params){
    Q_UNUSED(callbackID);
    Q_UNUSED(params);
    int modem = 0;

    qDebug() << Q_FUNC_INFO << "callbackID:" << callbackID << ", params: " << params << endl;
     QString date = params.value("date").toString();
   
    QDBusMessage dbusMessage = QDBusMessage::createMethodCall(COMPOSITOR_SERVICE_NAME,
                                                              COMPOSITOR_OBJECT_PATH,
                                                              COMPOSITOR_INTERFACE_NAME,
                                                              "setTime");
    QDateTime dt = QDateTime::fromString(date, "yyyy-MM-dd hh:mm:ss");
    qDebug() << "time " << dt.toString();
    dbusMessage << dt.toString();
    qDebug() << QDBusConnection::systemBus().send(dbusMessage);

    QJsonObject jsonObject;
    jsonObject.insert("date", date);
    
    QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);

    qDebug() << Q_FUNC_INFO << "jsonObject:" << jsonObject << ", jsonObjectValue: " << jsonObjectValue << endl;

    signalManager()->success(callbackID.toLong(), QVariant(jsonObject));
}


void System::getResolution(QString callbackID,QVariantMap params){

    Q_UNUSED(params);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect mm = screen->availableGeometry() ;
    int width = mm.width();
    int height = mm.height();

    QJsonObject screenObj;
    screenObj.insert("width", width);
    screenObj.insert("height", height);

    qDebug() << Q_FUNC_INFO << "width:" << width << ", height: " << height << endl;
    signalManager()->success(callbackID.toLong(), QVariant(screenObj));
}

void System::getCoreVersion(QString callbackID,QVariantMap params){
    Q_UNUSED(params);
    COsInfo info;
    QString version = info.kernelVersion();
    qDebug() << Q_FUNC_INFO << "version" << version << endl;;
    signalManager()->success(callbackID.toLong(), QVariant(version));
}

void System::getSysVersionID(QString callbackID,QVariantMap params){
    Q_UNUSED(params);
    COsInfo info;
    QString version = info.osVersion();
    qDebug() << Q_FUNC_INFO << "version" << version << endl;;
    signalManager()->success(callbackID.toLong(), QVariant(version));
}
