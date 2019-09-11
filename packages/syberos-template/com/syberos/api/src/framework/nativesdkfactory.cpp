#include "nativesdkfactory.h"
#include <QDebug>

NativeSdkFactory::NativeSdkFactory(){

}
NativeSdkFactory::~NativeSdkFactory(){
    m_sdkHandlerCache.clear();

}
NativeSdkHandlerBase *  NativeSdkFactory::getHandler(QString typeID){
    if(m_sdkHandlerCache.contains(typeID)){
        m_sdkInitConnectCache.insert(typeID,true);
        return m_sdkHandlerCache.value(typeID);

    }
    int type = QMetaType::type(typeID.toLatin1().data());
    NativeSdkHandlerBase * instance=NULL;
    const QMetaObject *metaObj = QMetaType::metaObjectForType(type);
    if(metaObj){
        QObject *obj = metaObj->newInstance();
        NativeSdkHandlerBase * instance = qobject_cast<NativeSdkHandlerBase*>(obj);
        m_sdkHandlerCache.insert(typeID,instance);
        m_sdkInitConnectCache.insert(typeID,false);
        return instance;
    }else{
        return instance;
    }


}
QMap<QString,NativeSdkHandlerBase*> NativeSdkFactory::getAllHandlers(){
    return m_sdkHandlerCache;
}
bool NativeSdkFactory::IsInitConnect(QString typeID){
    return m_sdkInitConnectCache.value(typeID);
}

