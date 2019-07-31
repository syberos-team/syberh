#include "natviesdkfactory.h"
#include <QDebug>

NativeSdkFactory::NativeSdkFactory(){

}
NativeSdkFactory::~NativeSdkFactory(){

}
NativeSdkHandlerBase *  NativeSdkFactory::getHandler(QString typeID){
    if(m_sdkHandlerCache.contains(typeID)){
        return m_sdkHandlerCache.value(typeID);
    }
    int type = QMetaType::type(typeID.toLatin1().data());
    const QMetaObject *metaObj = QMetaType::metaObjectForType(type);
    QObject *obj = metaObj->newInstance();
    NativeSdkHandlerBase * instance = qobject_cast<NativeSdkHandlerBase*>(obj);
    m_sdkHandlerCache.insert(typeID,instance);
    return instance;

}
QMap<QString,NativeSdkHandlerBase*> NativeSdkFactory::getAllHandlers(){
    return m_sdkHandlerCache;
}

