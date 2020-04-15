#include "nativesdkfactory.h"
#include "pluginadapter.h"
#include "../../../pluginmanager/src/pluginmanager.h"
#include "../../../pluginmanager/src/pluginspec.h"
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
static inline PluginSpec* loadPlugin(QString className, QString *errorMessage){
    PluginManager *pluginManager = PluginManager::instance();

    QString name = className.remove("*").trimmed();
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

        bool isDone = plugin->initialize(spec->arguments(), errorMessage);
        if(!isDone){
            return nullptr;
        }
        plugin->extensionsInitialized();
        //TODO 考虑是否需要做延迟加载

        return spec;
    }
    return nullptr;
}


NativeSdkHandlerBase *  NativeSdkFactory::getHandler(QString className){
    if(m_sdkHandlerCache.contains(className)){
        m_sdkInitConnectCache.insert(className, true);
        return m_sdkHandlerCache.value(className);

    }
    int type = QMetaType::type(className.toLatin1().data());

    // 通过反射加载模块，若使用发射未找到模块时，尝试通过插件加载
    const QMetaObject *metaObj = QMetaType::metaObjectForType(type);
    if(metaObj){
        QObject *obj = metaObj->newInstance();
        NativeSdkHandlerBase *instance = qobject_cast<NativeSdkHandlerBase*>(obj);
        m_sdkHandlerCache.insert(className, instance);
        m_sdkInitConnectCache.insert(className, false);
        return instance;
    }
    //使用反射未找到模块，加载插件
    QString errorMessage;
    PluginSpec *pluginSpec = loadPlugin(className, &errorMessage);
    if(pluginSpec == nullptr){
        qDebug() << errorMessage;
        return nullptr;
    }
    PluginAdapter *adapter = new PluginAdapter();
    adapter->setPluginSpec(pluginSpec);
    m_sdkHandlerCache.insert(className, adapter);
    m_sdkInitConnectCache.insert(className, false);
    return adapter;


}

QMap<QString,NativeSdkHandlerBase*> NativeSdkFactory::getAllHandlers(){
    return m_sdkHandlerCache;
}

bool NativeSdkFactory::IsInitConnect(QString typeID){
    return m_sdkInitConnectCache.value(typeID);
}

}
