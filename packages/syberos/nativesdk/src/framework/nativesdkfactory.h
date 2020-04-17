#ifndef NATVIESDKFACTORY_H
#define NATVIESDKFACTORY_H

#include <QObject>
#include <QMap>

#include "../nativesdk_global.h"
#include "nativesdkhandlerbase.h"
#include "../../../pluginmanager/src/pluginspec.h"


namespace NativeSdk {

/**
 * @brief The NativeSdkFactory class
 * 业务处理模块工厂类
 */
class NATIVESDK_EXPORT NativeSdkFactory :public QObject{
    Q_OBJECT
public:
    NativeSdkFactory();
    ~NativeSdkFactory();
    /**
     * @brief getHandler
     * @param typeID 业务类的typeID
     * @return 对应typeID的业务类实例指针
     */
    NativeSdkHandlerBase * getHandler(QString typeID);
    QMap<QString,NativeSdkHandlerBase*>getAllHandlers();
    bool IsInitConnect(QString typeID);

    ExtensionSystem::PluginSpec* loadPlugin(QString className, QString *errorMessage);
private :
    QMap<QString,NativeSdkHandlerBase*> m_sdkHandlerCache;
    QMap<QString,bool> m_sdkInitConnectCache;

};

}
#endif // NATVIESDKFACTORY_H
