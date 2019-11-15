#include "helper.h"
#include "httpclient.h"
#include <cenvironment.h>
#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextCodec>
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

Helper::Helper(QObject *parent) : QObject(parent)
{
  env = new CEnvironment(this);
  appInfo = new CAppInfo();
  extendConfig = ExtendedConfig::instance();
}

QString Helper::logLevelName()
{
  QString levelName = ExtendedConfig::instance()->get("DEV_LOG").toString();
  if (levelName.isEmpty())
  {
    bool debug = ExtendedConfig::instance()->get("debug").toBool();
    if (debug)
    {
      levelName = "verbose";
    }
    else
    {
      levelName = "info";
    }
  }

  qDebug() << Q_FUNC_INFO << "levelName" << levelName << endl;
  return levelName;
}

bool Helper::exists(QString filePath)
{
  QFile file(filePath);
  return file.exists();
}

QString Helper::getWebRootPath()
{
  extendConfig = ExtendedConfig::instance();
  QVariant debug = extendConfig->get("debug");
  if (debug.toBool())
  {
    qDebug() << "webroot:" << this->getDataWebRootPath();
    return this->getDataWebRootPath();
  }
  else
  {
    return this->getDefaultWebRootPath();
  }
}

QString Helper::getDefaultWebRootPath()
{
  QDir dir(qApp->applicationDirPath());
  dir.cdUp();
  dir.cd("www");
  return dir.absolutePath();
}

QString Helper::getDataWebRootPath()
{
  QString path = this->getDataRootPath() + "/www";
  return path;
}

QString Helper::getDataRootPath()
{
  return env->dataPath();
}

QString Helper::getExternStorageRootPath()
{
  return env->externalStoragePath();
}

QString Helper::getInnerStorageRootPath()
{
  return env->internalStoragePath();
}

QString Helper::sopid()
{
  return qApp->property("sopid").toString();
}

QString Helper::getQtVersion()
{
  return QT_VERSION_STR;
}

bool Helper::isGtQt56()
{
  return QT_VERSION >= QT_VERSION_CHECK(5, 6, 0);
}

QJsonObject Helper::aboutPhone()
{

  int modem = 0;

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
  QRect mm = screen->availableGeometry();
  int screenWidth = mm.width();
  int screenHeight = mm.height();
  qreal pixelRatio = screen->devicePixelRatio(); //设备像素比
  QLocale locale;
  QJsonValue language = QJsonValue::fromVariant(QLocale::languageToString(locale.language())); //获取系统语言
  QJsonValue region = locale.countryToString(locale.country());                                //获取系统地区

  QJsonObject jsonObject;
  jsonObject.insert("deviceId", deviceId);
  jsonObject.insert("brand", "");                            //设备品牌
  jsonObject.insert("manufacturer", "");                     //设备生产商
  jsonObject.insert("model", "");                            //设备型号
  jsonObject.insert("name", name);                           //手机名称
  jsonObject.insert("imei", imei);                           //移动设备国际识别码
  jsonObject.insert("simCardNumbers", simcardNumberJsonArr); //如果是双卡，有多个手机号
  jsonObject.insert("imsis", imsisJsonArr);                  //如果是双卡，有多个国际移动用户识别码
  jsonObject.insert("osType", "Syber");                      //操作系统名称
  jsonObject.insert("osVersionName", softwareVersion);       //操作系统版本名称
  jsonObject.insert("osVersion", osVersion);                 //操作系统版本号
  jsonObject.insert("osVersionCode", osVersionCode);         //操作系统小版本号
  jsonObject.insert("kernelVersion", kernelVersion);         //内核版本号
  jsonObject.insert("screenWidth", screenWidth);             //屏幕宽
  jsonObject.insert("screenHeight", screenHeight);           //屏幕高
  jsonObject.insert("windowWidth", "");                      //可使用窗口宽度
  jsonObject.insert("windowHeight", "");                     //可使用窗口高度
  jsonObject.insert("pixelRatio", pixelRatio);               //设备像素比
  jsonObject.insert("statusBarHeight", "");                  //状态栏的高度 （待实现）
  jsonObject.insert("language", language);                   //系统语言
  jsonObject.insert("region", region);                       //系统地区

  QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);
  qDebug() << "aboutphone: " << jsonObject << endl;
  return jsonObject;
}

bool Helper::emptyDir(const QString &path)
{
  if (path.isEmpty())
  {
    return false;
  }
  QDir dir(path);
  if (!dir.exists())
  {
    return true;
  }
  dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
  QFileInfoList fileList = dir.entryInfoList();
  foreach (QFileInfo fi, fileList)
  {
    if (fi.isFile())
    {
      fi.dir().remove(fi.fileName());
      //qDebug() <<"filename:" <<fi.fileName() <<f;
    }
    else
    {
      this->emptyDir(fi.absoluteFilePath());
    }
  }
  return dir.rmpath(dir.absolutePath());
}

bool Helper::isPicture(QString filepath)
{
  QMimeDatabase db;
  QMimeType mime = db.mimeTypeForFile(filepath);
  qDebug() << Q_FUNC_INFO << "isPicture, mime: " << filepath << mime.name() << endl;
  return mime.name().startsWith("image/");
}

bool Helper::isAudio(QString filepath)
{
  QMimeDatabase db;
  QMimeType mime = db.mimeTypeForFile(filepath);
  qDebug() << Q_FUNC_INFO << "isAudio, mime: " << filepath << mime.name() << endl;
  return mime.name().startsWith("audio/");
}
