#include "nativesdkmanager.h"
#include <QMutexLocker>
#include <QDebug>

NativeSdkManager* NativeSdkManager::m_pNativeSdkManager = NULL;
NativeSdkManager::NativeSdkManager(){
    extendConfig= ExtendedConfig::instance();
    QVariant debug = extendConfig->get("debug");
    if(debug.toBool()){
        if(!devTools){
             devTools=DevTools::getInstance();
        }
    }
    qDebug() <<Q_FUNC_INFO<< "$$$ debug:" << debug << debug.isValid() << endl;
}
NativeSdkManager::~NativeSdkManager(){
    QMap<QString,NativeSdkHandlerBase*> handlers = m_NativeSdkFactory.getAllHandlers();
    QMapIterator<QString,NativeSdkHandlerBase*> i(handlers);
    while (i.hasNext()) {
        i.next();
        NativeSdkHandlerBase * handler = i.value();
        if(handler){
            disconnect(handler,SIGNAL(success(long,QVariant)),this,SIGNAL(success(long,QVariant)));
            disconnect(handler,SIGNAL(failed(long,long,QString)),this,SIGNAL(failed(long,long,QString)));
            disconnect(handler,SIGNAL(progress(long,int,int,int)),this,SIGNAL(progress(long,int,int,int)));
            disconnect(handler,SIGNAL(subscribe(QString,QVariant)),this,SIGNAL(subscribe(QString,QVariant)));
            delete handler;
            handler = NULL;
        }
    }
    if(m_pNativeSdkManager){
        delete m_pNativeSdkManager;
        m_pNativeSdkManager = NULL;
    }


}
NativeSdkManager * NativeSdkManager::getInstance(){
    static QMutex mutex;
    if(m_pNativeSdkManager == NULL){
        QMutexLocker locker(&mutex);
        if(m_pNativeSdkManager == NULL){
              m_pNativeSdkManager = new NativeSdkManager;
        }
    }
    return m_pNativeSdkManager;
}

void NativeSdkManager::openByUrl(const QUrl& url){
    QVariantMap params;
    params.insert("url", url.toString());
    request("Package*","123","openByUrl", params);
}

void NativeSdkManager::openByDocument(const QString& action, const QString& mimetype,
                                      const QString& filePath){
    QVariantMap params;
    params.insert("action", action);
    params.insert("mimetype", mimetype);
    params.insert("filePath", filePath);
    request("Package*","321","openByDocument", params);
}

void NativeSdkManager::request(QString className,QString callBackID,QString actionName,QVariantMap params){
    NativeSdkHandlerBase * handler = m_NativeSdkFactory.getHandler(className);
    if(handler){
        if(!m_NativeSdkFactory.IsInitConnect(className))
            initHandlerConnect(className);
        handler->request(callBackID,actionName,params);

    }else{
        QString msg="Native SDK 模块不存在：["+className+"]";
        long handlerId=callBackID.toLong();
        long code=1009;
        emit failed(handlerId,code,msg);
        qDebug()<< msg;
    }

}
void NativeSdkManager::submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes){

    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
}
QObject * NativeSdkManager::getUiSource(QString typeID,QString actionName){
    NativeSdkHandlerBase * handler = m_NativeSdkFactory.getHandler(typeID);
    QObject * item = NULL;
    if(handler){
        if(!m_NativeSdkFactory.IsInitConnect(typeID))
            initHandlerConnect(typeID);
        item =  handler->getUiSource(actionName);
    }
    return item;
}
void NativeSdkManager::initHandlerConnect(QString typeID){
    NativeSdkHandlerBase * handler = m_NativeSdkFactory.getAllHandlers().value(typeID);
    if(handler){
        connect(handler,SIGNAL(success(long,QVariant)),this,SIGNAL(success(long,QVariant)));
        connect(handler,SIGNAL(failed(long,long,QString)),this,SIGNAL(failed(long,long,QString)));
        connect(handler,SIGNAL(progress(long,int,int,int)),this,SIGNAL(progress(long,int,int,int)));
        connect(handler,SIGNAL(subscribe(QString,QVariant)),this,SIGNAL(subscribe(QString,QVariant)));
    }
}
void NativeSdkManager::loadQml(QString typeID,QString parentPageName, QString parentName, QString type){
    NativeSdkHandlerBase * handler = m_NativeSdkFactory.getHandler(typeID);
    if(handler){
        if(!m_NativeSdkFactory.IsInitConnect(typeID))
            initHandlerConnect(typeID);
        handler->loadQml(parentPageName,parentName,type);
    }
}

