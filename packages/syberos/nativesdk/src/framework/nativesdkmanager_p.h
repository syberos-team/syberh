#ifndef NATIVESDKMANAGER_P_H
#define NATIVESDKMANAGER_P_H

#include <QObject>
#include "common/errorinfo.h"


namespace NativeSdk {

class NativeSdkManager;
class NativeSdkFactory;
class ExtendedConfig;
class DevTools;
class PluginSpec;

namespace Internal {

class NativeSdkManagerPrivate : public QObject{
    Q_OBJECT
public:
    NativeSdkManagerPrivate(NativeSdkManager *nativeSdkManager);
    ~NativeSdkManagerPrivate();

    NativeSdkFactory *nativeSdkFactory;
    //拓展配置
    ExtendedConfig *extendConfig = nullptr;
    //开发工具
    DevTools *devTools = nullptr;

public slots:
    //加载所有插件
    void loadPlugins();
    //关闭所有插件
    void shutdownPlugins();

private:
    NativeSdkManager *manager;
    QMap<QString, PluginSpec*> pluginCache;
};
}
}
#endif // NATIVESDKMANAGER_P_H
