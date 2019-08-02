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
     * @param className 业务类的typeID
     * @return 对应typeID的业务类实例指针
     */
    NativeSdkHandlerBase * getHandler(QString className);
     QMap<QString,NativeSdkHandlerBase*>getAllHandlers();
private :
    QMap<QString,NativeSdkHandlerBase*> m_sdkHandlerCache;

};

#endif // NATVIESDKFACTORY_H
