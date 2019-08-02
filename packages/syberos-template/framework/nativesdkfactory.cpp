#include "natviesdkfactory.h"
#include <QDebug>

NativeSdkFactory::NativeSdkFactory(){

}
NativeSdkFactory::~NativeSdkFactory(){

}
NativeSdkHandlerBase *  NativeSdkFactory::getHandler(QString className){
    if(m_sdkHandlerCache.contains(className)){
        return m_sdkHandlerCache.value(className);
    }
    int type = QMetaType::type(className.toLatin1().data());
    const QMetaObject *metaObj = QMetaType::metaObjectForType(type);
    QObject *obj = metaObj->newInstance();
    NativeSdkHandlerBase * instance = qobject_cast<NativeSdkHandlerBase*>(obj);
    m_sdkHandlerCache.insert(className,instance);
    return instance;

}
QMap<QString,NativeSdkHandlerBase*> NativeSdkFactory::getAllHandlers(){
    return m_sdkHandlerCache;
}

