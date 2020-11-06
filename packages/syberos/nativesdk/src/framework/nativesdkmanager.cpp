#include "nativesdkmanager.h"
#include "nativesdkmanager_p.h"
#include "nativesdkfactory.h"
#include "nativesdkhandlerbase.h"
#include "common/projectconfig.h"
#include "devtools/devtools.h"
#include "../../../pluginmanager/src/pluginmanager.h"
#include "../../../pluginmanager/src/pluginspec.h"
#include "../../../pluginmanager/src/iplugin/iplugin.h"

#include <QMutexLocker>
#include <QDebug>
#include <qguiapplication.h>
#include <QSettings>

#define SETTING_ORG "SyberOS"
#define SETTING_APP "Syberh"
#define PLUGIN_IID "com.syberos.syberh.SyberhPlugin"
#define PLUGIN_DIR_NAME "plugins"

using namespace ExtensionSystem;

namespace NativeSdk {

using namespace Internal;

// ========== NativeSdkManager ^ ==========

NativeSdkManager* NativeSdkManager::m_pNativeSdkManager = nullptr;

NativeSdkManager::NativeSdkManager() {
    d = new NativeSdkManagerPrivate(this);
    d->nativeSdkFactory = new NativeSdkFactory();
    //加载插件
    d->loadPlugins();

    d->projectConfig = ProjectConfig::instance();
    bool useHot = d->projectConfig->isUseHot();
    if(useHot){
        if(!d->devTools){
             d->devTools = DevTools::getInstance();
        }
    }
    qDebug() <<Q_FUNC_INFO<< "$$$ use hot:" << useHot << endl;
}

NativeSdkManager::~NativeSdkManager(){
    if(d != nullptr){
        delete d;
        d = nullptr;
    }
    if(m_pNativeSdkManager){
        delete m_pNativeSdkManager;
        m_pNativeSdkManager = nullptr;
    }
}

NativeSdkManager * NativeSdkManager::getInstance(){
    static QMutex mutex;
    if(m_pNativeSdkManager == nullptr){
        QMutexLocker locker(&mutex);
        if(m_pNativeSdkManager == nullptr){
              m_pNativeSdkManager = new NativeSdkManager;
        }
    }
    return m_pNativeSdkManager;
}

void NativeSdkManager::openByUrl(const QUrl& url){
    QVariantMap params;
    params.insert("url", url.toString());
    request("Packages*","123","openByUrl", params);
}

void NativeSdkManager::openByDocument(const QString& action, const QString& mimetype,
                                      const QString& filePath){
    QVariantMap params;
    params.insert("action", action);
    params.insert("mimetype", mimetype);
    params.insert("filePath", filePath);
    request("Packages*","321","openByDocument", params);
}

void NativeSdkManager::request(QString className,QString callbackID,QString actionName,QVariantMap params){
    qDebug() << "className:" << className << "callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    NativeSdkHandlerBase * handler = d->nativeSdkFactory->getHandler(className);
    if(handler){
        if(!d->nativeSdkFactory->IsInitConnect(className))
            initHandlerConnect(className);
        handler->request(callbackID,actionName,params);
        return;
    }
    long handlerId = callbackID.toLong();
    QString msg = ErrorInfo::message(ErrorInfo::UndefinedModule, className);
    emit failed(handlerId, ErrorInfo::UndefinedModule, msg);
    qDebug() << msg;
}


void NativeSdkManager::initHandlerConnect(QString typeID){
    NativeSdkHandlerBase * handler = d->nativeSdkFactory->getAllHandlers().value(typeID);
    if(handler){
        connect(handler,SIGNAL(success(long,QVariant)),this,SIGNAL(success(long,QVariant)));
        connect(handler,SIGNAL(failed(long,long,QString)),this,SIGNAL(failed(long,long,QString)));
        connect(handler,SIGNAL(progress(long,int,int,int)),this,SIGNAL(progress(long,int,int,int)));
        connect(handler,SIGNAL(subscribe(QString,QVariant)),this,SIGNAL(subscribe(QString,QVariant)));
    }
}
// ========== NativeSdkManager & ==========


// ========== NativeSdkManagerPrivate ^ ==========
NativeSdkManagerPrivate::NativeSdkManagerPrivate(NativeSdkManager *nativeSdkManager)
{
    manager = nativeSdkManager ;
}

NativeSdkManagerPrivate::~NativeSdkManagerPrivate(){
    //清理 nativeSdkFactory，清除缓存
    if(nativeSdkFactory != nullptr){
        QMap<QString,NativeSdkHandlerBase*> handlers = nativeSdkFactory->getAllHandlers();
        QMapIterator<QString,NativeSdkHandlerBase*> i(handlers);
        while (i.hasNext()) {
            i.next();
            NativeSdkHandlerBase * handler = i.value();
            if(handler){
                QObject::disconnect(handler, 0, 0, 0);
                delete handler;
                handler = nullptr;
            }
        }
        delete nativeSdkFactory;
        nativeSdkFactory = nullptr;
    }

    if(projectConfig != nullptr){
        delete projectConfig;
        projectConfig = nullptr;
    }
    if(devTools != nullptr){
        delete devTools;
        devTools = nullptr;
    }
    manager = nullptr;
    // 关闭插件
    emit shutdownPlugins();
}

/**
 * @brief 获取插件目录
 * @param appDirPath 应用目录，由 qApp->applicationDirPath() 获取
 * @return
 */
static inline QStringList getPluginPaths(const QString &appDirPath){
    QDir dir(appDirPath);
    dir.cdUp();
    dir.cd(QLatin1String(PLUGIN_DIR_NAME));
    return QStringList(dir.absolutePath());
}

//加载插件
void NativeSdkManagerPrivate::loadPlugins()
{
    QSettings *globalSettings = new QSettings(QSettings::IniFormat, QSettings::SystemScope,
                                              QLatin1String(SETTING_ORG),
                                              QLatin1String(SETTING_APP));
    QSettings *settings = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                                        QLatin1String(SETTING_ORG),
                                        QLatin1String(SETTING_APP));
    QLatin1String pluginIID = QLatin1String(PLUGIN_IID);
    const QStringList pluginPaths = getPluginPaths(qApp->applicationDirPath());
    qDebug() << "PLUGIN_IID:" << pluginIID << "pluginPaths:" << pluginPaths;

    PluginManager::instance();
    PluginManager::setPluginIID(pluginIID);
    PluginManager::setGlobalSettings(globalSettings);
    PluginManager::setSettings(settings);
    PluginManager::setPluginPaths(pluginPaths);
    PluginManager::loadPlugins();
}

void NativeSdkManagerPrivate::shutdownPlugins()
{
    PluginManager *manager = PluginManager::instance();
    if(manager != nullptr){
        manager->shutdown();
    }
}
// ========== NativeSdkManagerPrivate & ==========

} // END NativeSdk
