#include "projectconfig.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QMutexLocker>
#include <QFileInfo>
#include <QFile>
#include <qguiapplication.h>
#include <QDir>


#define PROJECT_CONFIG_FILENAME "project.config.json"

namespace NativeSdk {

QString appRootPath()
{
    QDir dir(qApp->applicationDirPath());
    dir.cdUp();
    return QString("%1/%2")
            .arg(dir.absolutePath())
            .arg(PROJECT_CONFIG_FILENAME);
}

ProjectConfig* ProjectConfig::_instance = nullptr;

ProjectConfig::ProjectConfig(QObject *parent) : QObject(parent), d(new ProjectConfigPrivate)
{
}

ProjectConfig::~ProjectConfig(){
    delete d;
    delete _instance;
    d = nullptr;
    _instance = nullptr;
}

void ProjectConfig::load(){
    qDebug() << Q_FUNC_INFO;
    bool isLoaded = d->load();
    if(!isLoaded){
        qDebug() << Q_FUNC_INFO << "load fail:" << d->errorMessage();
    }
}

ProjectConfig* ProjectConfig::instance(){
    static QMutex mutex;
    if(_instance == nullptr){
        QMutexLocker locker(&mutex);
        if(_instance == nullptr){
              _instance = new ProjectConfig;
              _instance->load();
        }
    }
    return _instance;
}

QString ProjectConfig::getLogLevel()
{
    return d->getString("logLevel");
}

bool ProjectConfig::isDebug()
{
    return d->getBool("debug");
}

bool ProjectConfig::isUseHot()
{
    return d->getBool("hot");
}

QString ProjectConfig::getProjectName()
{
    return d->getString("projectName");
}

QString ProjectConfig::getAppName()
{
    return d->getString("appName");
}

QString ProjectConfig::getSopid()
{
    return d->getString("sopid");
}

QString ProjectConfig::getTarget()
{
    return d->getString("target");
}

QString ProjectConfig::getTargetSimulator()
{
    return d->getString("targetSimulator");
}

QString ProjectConfig::getWebPath()
{
    return d->getString("webPath");
}

QString ProjectConfig::getHomePage()
{
    return d->getString("homePage");
}

QString ProjectConfig::getStoreBaseUrl()
{
    return d->getString("storeBaseUrl");
}

QString ProjectConfig::getDeployIP()
{
    return d->getString("deployIP");
}

QString ProjectConfig::getDeployPort()
{
    return d->getString("deployPort");
}

QString ProjectConfig::getDevServerIP()
{
    return d->getString("devServerIP");
}

QString ProjectConfig::getDevServerPort()
{
    return d->getString("devServerPort");
}

QString ProjectConfig::getDebuggingPort()
{
    return d->getString("debuggingPort");
}

bool ProjectConfig::statusBarShow()
{
    return d->getBool("statusBar","show");
}

QString ProjectConfig::statusBarStyle()
{
     QString style=d->getString("statusBar","style");
     if(style.isEmpty()){
         style="black";
     }
     return style;
}



// ---- ProjectConfigPrivate ----
bool ProjectConfigPrivate::load()
{
    //从应用根目录中读取project.config.json
    QString configPath = appRootPath();
    if(!QFileInfo::exists(configPath)){
        setErrorMessage(QString("cannot find file: ") + configPath);
        return false;
    }
    QFile file(configPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "ProjectConfigPrivate::load()  cannot open file:" << configPath << ", error:" << file.errorString();
        setErrorMessage(QString("cannot open file: ") + configPath);
        return false;
    }
    QByteArray data = file.readAll();
    qDebug() << "ProjectConfigPrivate::load()  file:" << configPath << ", content:" << data;
    file.close();

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &jsonError);
    if(doc.isNull() || jsonError.error != QJsonParseError::NoError){
        qDebug() << "ProjectConfigPrivate::load()  cannot parse json:" << configPath << ", error:" << jsonError.errorString();
        setErrorMessage(QString("cannot parse json file: ") + configPath);
        return false;
    }
    if(doc.isEmpty()){
        qDebug() << "ProjectConfigPrivate::load()  json file empty:" << configPath;
        setErrorMessage(QString("json file empty: ") + configPath);
        return false;
    }
    conf = doc.object();
    return true;
}

QString ProjectConfigPrivate::errorMessage()
{
    return errMsg;
}

void ProjectConfigPrivate::setErrorMessage(const QString &msg)
{
    errMsg = msg;
}

QString ProjectConfigPrivate::getString(const QString &key)
{
    QJsonValue jsonValue = getValue(key);
    if(!jsonValue.isString()){
        return QString();
    }
    return jsonValue.toString();
}

QString ProjectConfigPrivate::getString(const QString &key, const QString &key2)
{
    QJsonValue jsonValue = getValue(key, key2);
    if(!jsonValue.isString()){
        return QString();
    }
    return jsonValue.toString();
}

bool ProjectConfigPrivate::getBool(const QString &key)
{
    QJsonValue jsonValue = getValue(key);
    if(!jsonValue.isBool()){
        return false;
    }
    return jsonValue.toBool();
}

bool ProjectConfigPrivate::getBool(const QString &key, const QString &key2)
{
    QJsonValue jsonValue = getValue(key, key2);
    if(!jsonValue.isBool()){
        return false;
    }
    return jsonValue.toBool();
}

QJsonValue ProjectConfigPrivate::getValue(const QString &key)
{
    if(conf.isEmpty()){
        return QJsonValue();
    }
    return conf.value(key);
}

QJsonValue ProjectConfigPrivate::getValue(const QString &key, const QString &key2)
{
    if(conf.isEmpty()){
        return QJsonValue();
    }
    QJsonValue jsonValue = conf.value(key);
    if(jsonValue.isUndefined() || jsonValue.isNull() || !jsonValue.isObject()){
        return QJsonValue();
    }
    QJsonObject jsonObj = jsonValue.toObject();
    if(jsonObj.isEmpty()){
        return QJsonValue();
    }
    return jsonObj.value(key2);
}

}
