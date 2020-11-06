#include "helper.h"
#include <cenvironment.h>
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
#include <QMimeDatabase>
#include <QMutexLocker>

#include "helper_p.h"
#include "framework/common/projectconfig.h"

namespace NativeSdk {

Helper *Helper::helper = nullptr;

Helper::Helper(QObject *parent) : QObject(parent)
{
    d = new Internal::HelperPrivate();
    d->env = new CEnvironment(this);
}

Helper::~Helper()
{
    delete d;
    d = nullptr;
}

QString Helper::logLevelName()
{
  QString levelName;
  bool debug = ProjectConfig::instance()->isDebug();
  if (debug)
  {
    levelName = "verbose";
  }
  else
  {
    levelName = "info";
  }

  qDebug() << "levelName" << levelName << endl;
  return levelName;
}

bool Helper::exists(QString filePath)
{
  QFile file(filePath);
  return file.exists();
}



Helper *Helper::instance()
{
    static QMutex mutex;
    if(helper == nullptr){
        QMutexLocker locker(&mutex);
        if(helper == nullptr){
              helper = new Helper;
        }
    }
    return helper;
}

QString Helper::getWebRootPath()
{
  //TODO 5.0暂时不使用热更新目录
  #if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
    return this->getDefaultWebRootPath();
  #else
    bool useHot = ProjectConfig::instance()->isUseHot();
    if (useHot)
    {
      qDebug() << "webroot:" << this->getDataWebRootPath();
      return this->getDataWebRootPath();
    }
    else
    {
      return this->getDefaultWebRootPath();
    }
  #endif
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
  return d->env->dataPath();
}

QString Helper::getExternStorageRootPath()
{
  return d->env->externalStoragePath();
}

QString Helper::getInnerStorageRootPath()
{
  return d->env->internalStoragePath();
}

QString Helper::sopid()
{
  return qApp->property("sopid").toString();
}

qint32 Helper::getQtVersion()
{
  return QT_VERSION;
}

QString Helper::getQtVersionName()
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

QString Helper::getHomePage()
{
  QString page = ProjectConfig::instance()->getHomePage();
  if(page.isEmpty()){
    QString dir = getWebRootPath();
    page = QString("file://%1/index.html").arg(dir);
  }
  return page;
}

// ========== HelperPrivate ^ ==========

namespace Internal {

HelperPrivate::~HelperPrivate()
{
    if(env != nullptr){
        env->deleteLater();
        env = nullptr;
    }
}

}
// ========== HelperPrivate & ==========

}
