#include "pluginadapter.h"
#include "../../../pluginmanager/src/iplugin/iplugin.h"
#include "common/errorinfo.h"

using namespace ExtensionSystem;

namespace NativeSdk {

PluginAdapter::PluginAdapter(){

}

PluginAdapter::~PluginAdapter(){
}

void PluginAdapter::setPluginSpec(PluginSpec *spec){
    pluginSpec = spec;
    IPlugin *plugin = pluginSpec->plugin();
    SignalManager *signalManager = plugin->signalManager();

    QObject::connect(signalManager, &SignalManager::success, this, &PluginAdapter::success);
    QObject::connect(signalManager, &SignalManager::failed, this, &PluginAdapter::failed);
    QObject::connect(signalManager, &SignalManager::progress, this, &PluginAdapter::progress);
    QObject::connect(signalManager, &SignalManager::subscribe, this, &PluginAdapter::subscribe);
}

void PluginAdapter::request(QString callbackID,QString actionName,QVariantMap params){
    if(pluginSpec == nullptr){
            //插件未找到
        emit failed(callbackID.toLong(), ErrorInfo::PluginError, "插件未加载");
        return;
    }
    if(pluginSpec->state() < PluginSpec::Running){
        //插件未加载完成
        emit failed(callbackID.toLong(), ErrorInfo::PluginError, "插件未加载完成");
    }else if(pluginSpec->state() > PluginSpec::Running){
        //插件已卸载
        emit failed(callbackID.toLong(), ErrorInfo::PluginError, "插件已卸载");
    }else{
        IPlugin *plugin = pluginSpec->plugin();
        plugin->beforeInvoke();
        plugin->invoke(callbackID, actionName, params);
    }
}

}