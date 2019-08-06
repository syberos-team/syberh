#ifndef NATVIESDKFACTORY_H
#define NATVIESDKFACTORY_H

#include <QObject>
#include <QMap>
#include "nativesdkhandlerbase.h"
/**
 * @brief The NativeSdkFactory class
 * 业务处理模块工厂类
 */
class NativeSdkFactory :public QObject{
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
private :
    QMap<QString,NativeSdkHandlerBase*> m_sdkHandlerCache;
    QMap<QString,bool> m_sdkInitConnectCache;

};

#endif // NATVIESDKFACTORY_H
