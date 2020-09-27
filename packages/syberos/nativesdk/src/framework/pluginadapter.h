#ifndef PLUGINADAPTER_H
#define PLUGINADAPTER_H

#include <QObject>
#include <QVariantMap>

#include "nativesdkhandlerbase.h"
#include "./common/networkstatus.h"
#include "./common/errorinfo.h"
#include "../../../pluginmanager/src/pluginspec.h"

namespace NativeSdk {
/**
 * @brief 将模块加载模式与插件加载融合
 */
class PluginAdapter : public NativeSdkHandlerBase{
    Q_OBJECT
public:
    Q_INVOKABLE PluginAdapter();
    ~PluginAdapter();

    void setPluginSpec(ExtensionSystem::PluginSpec *spec);

    void request(QString callbackID,QString actionName,QVariantMap params);

private:
    ExtensionSystem::PluginSpec *pluginSpec;
};
}
#endif // PLUGINADAPTER_H
