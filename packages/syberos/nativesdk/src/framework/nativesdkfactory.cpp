#include "nativesdkfactory.h"
#include "pluginadapter.h"
#include "../../../pluginmanager/src/pluginmanager.h"
#include "../../../pluginmanager/src/iplugin/iplugin.h"

#include <QDebug>

using namespace ExtensionSystem;

namespace NativeSdk {


NativeSdkFactory::NativeSdkFactory(){
}

NativeSdkFactory::~NativeSdkFactory(){
    m_sdkHandlerCache.clear();
    m_sdkInitConnectCache.clear();
}


//初始化指定的插件，若插件加载成功则返回否则返回空指针
PluginSpec* NativeSdkFactory::loadPlugin(QString className, QString *errorMessage){
    PluginManager *pluginManager = PluginManager::instance();

    QString name = className.remove("*").trimmed();

    qDebug() << "className:" << className << "PluginManager:" << pluginManager;

    QVector<PluginSpec *> pluginSpecs = pluginManager->plugins();
    foreach(PluginSpec *spec, pluginSpecs){
        if(spec->name() != name){
            continue;
        }
        IPlugin *plugin = spec->plugin();
        if(plugin == nullptr){
            *errorMessage = QString("未找到插件: %1").arg(name);
            return nullptr;
        }
        return spec;
    }
    return nullptr;
}


NativeSdkHandlerBase *  NativeSdkFactory::getHandler(QString className){
    if(m_sdkHandlerCache.contains(className)){
        m_sdkInitConnectCache.insert(className, true);
        qDebug() << "find module in cache:" << className;
        return m_sdkHandlerCache.value(className);
    }

    //首先使用加载方式尝试加载
    QString errorMessage;
    PluginSpec *pluginSpec = loadPlugin(className, &errorMessage);
    if(!errorMessage.isEmpty()){
        qDebug() << "load plugin failure:" << errorMessage;
    }
    if(pluginSpec != nullptr){
        PluginAdapter *adapter = new PluginAdapter();
        adapter->setPluginSpec(pluginSpec);

        m_sdkHandlerCache.insert(className, adapter);
        m_sdkInitConnectCache.insert(className, false);
        return adapter;
    }

    //通过反射加载模块
    int type = QMetaType::type(className.toLatin1().data());
    const QMetaObject *metaObj = QMetaType::metaObjectForType(type);
    if(metaObj){
        qDebug() << "find module by QMetaType:" << className << metaObj;
        QObject *obj = metaObj->newInstance();

        NativeSdkHandlerBase *instance = qobject_cast<NativeSdkHandlerBase*>(obj);

        m_sdkHandlerCache.insert(className, instance);
        m_sdkInitConnectCache.insert(className, false);
        return instance;
    }
    return nullptr;
}

QMap<QString,NativeSdkHandlerBase*> NativeSdkFactory::getAllHandlers(){
    return m_sdkHandlerCache;
}

bool NativeSdkFactory::IsInitConnect(QString typeID){
    return m_sdkInitConnectCache.value(typeID);
}

}
