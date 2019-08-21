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
#include <QSize>
#include <QTimeZone>

int System::typeId = qRegisterMetaType<System *>();
System::System()
{

}
System::~System()
{

}

void System::request(QString callBackID, QString actionName, QVariantMap params)
{
    Q_UNUSED(actionName)
    aboutPhone(callBackID.toLong(), params);
}

void System::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
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

    COsInfo info;
    QJsonValue hardware = QJsonValue::fromVariant(info.hardware());
    QJsonValue KernelVersion = QJsonValue::fromVariant(info.kernelVersion());
    QJsonValue osVersion = QJsonValue::fromVariant(info.osVersion());

    QJsonValue osVersionCode = QJsonValue::fromVariant(info.osVersionCode());
    QJsonValue softwareVersion = QJsonValue::fromVariant(info.softwareVersion());

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect mm = screen->availableGeometry() ;

    int width = mm.width();
    int height = mm.height();

    qreal pixelRatio = screen->devicePixelRatio();//设备像素比


//    //获取可用窗口高度
//    desktopAvailableHeight = height - statusBarHeight;
//    //获取可用窗口宽度
//    desktopAvailableWidth = width;

    QLocale locale;//获取系统语言
    QJsonValue language = QJsonValue::fromVariant(QLocale::languageToString(locale.language()));

    QTimeZone localPosition = QDateTime::currentDateTime().timeZone();//获取当前时区
    QJsonValue region = QJsonValue::fromVariant(localPosition.country());

    QJsonObject jsonObject;
    jsonObject.insert("id", id);
    jsonObject.insert("brand", "设备品牌");//设备品牌
    jsonObject.insert("manufacturer", "设备生产商");//设备生产商
    jsonObject.insert("model", "设备型号");//设备型号
    jsonObject.insert("name", name);//手机名称
    jsonObject.insert("imei", imei);//移动设备国际识别码
    jsonObject.insert("simcardNumber", sincardNumberJsonValue);//如果是双卡，有多个手机号
    jsonObject.insert("imsis", imsisJsonValue);//如果是双卡，有多个国际移动用户识别码
    jsonObject.insert("hardware", hardware);//系统的平台类型
    jsonObject.insert("KernelVersion", KernelVersion);//内核版本号
    jsonObject.insert("osVersion", osVersion);//系统版本号
    jsonObject.insert("osVersionCode", osVersionCode);//系统的小版本号。小版本号指的是系统小功能或者bugs升级对应的系统版本号。
    jsonObject.insert("softwareVersion", softwareVersion);//系统版本号的简称或者代号
    jsonObject.insert("height", height);
    jsonObject.insert("width", width);

//    jsonObject.insert("desktopAvailableHeight", desktopAvailableHeight);//可使用窗口高度
//    jsonObject.insert("desktopAvailableWidth", desktopAvailableWidth);//可使用窗口宽度

//    jsonObject.insert("statusBarHeight", statusBarHeight);//状态栏的高度

    jsonObject.insert("pixelRatio", pixelRatio);//设备像素比
    //jsonObject.insert("screenDensity", height);//设备的屏幕密度

    jsonObject.insert("language", language);//系统语言
    jsonObject.insert("region", region);//系统地区


    QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);
    qDebug() << "aboutPhone: " << jsonObjectValue.toString() << endl;
    qDebug() << "jsonObject: " << jsonObject << endl;
    emit success(callBackID, QVariant(jsonObject));
}

/*
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
*/
