#include "nativesdkmanager.h"
#include <QMutexLocker>
#include <QDebug>

NativeSdkManager* NativeSdkManager::m_pNativeSdkManager = NULL;
NativeSdkManager::NativeSdkManager(){

}
NativeSdkManager::~NativeSdkManager(){
    int size = m_List.size();
    for(int i = 0 ;i < size; i++){
        NativeSdkHandlerBase * handler = m_List.at(i);
        if(handler){
            disconnect(handler,SIGNAL(sucess(long,QVariant)),this,SIGNAL(sucess(long,QVariant)));
            disconnect(handler,SIGNAL(failed(long,long,QString)),this,SIGNAL(failed(long,long,QString)));
            disconnect(handler,SIGNAL(progress(long,int,int,int)),this,SIGNAL(progress(long,int,int,int)));
            delete handler;
            handler = NULL;
        }
    }
    m_List.clear();
    if(m_pNativeSdkManager){
        delete m_pNativeSdkManager;
        m_pNativeSdkManager = NULL;
    }


}
NativeSdkManager * NativeSdkManager::getInstance(){
    static QMutex mutex;
    if(m_pNativeSdkManager == NULL){
        QMutexLocker locker(&mutex);
        if(m_pNativeSdkManager == NULL)
            m_pNativeSdkManager = new NativeSdkManager;
    }
    return m_pNativeSdkManager;
}
void NativeSdkManager::request(QString className,QString callBackID,QString actionName,QVariantMap params){
    NativeSdkHandlerBase * handler = m_NativeSdkFactory.getHandler(className);
    if(handler){
        insertHandlerBase2List(handler);
        handler->request(callBackID,actionName,params);

    }

}
void NativeSdkManager::submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes){

}
void NativeSdkManager::insertHandlerBase2List(NativeSdkHandlerBase *handler){
    if(handler){
        if(!m_List.contains(handler)){
            m_List.append(handler);
            connect(handler,SIGNAL(sucess(long,QVariant)),this,SIGNAL(sucess(long,QVariant)));
            connect(handler,SIGNAL(failed(long,long,QString)),this,SIGNAL(failed(long,long,QString)));
            connect(handler,SIGNAL(progress(long,int,int,int)),this,SIGNAL(progress(long,int,int,int)));

        }
    }
}
QObject * NativeSdkManager::getUiSource(QString className,QString actionName){
    NativeSdkHandlerBase * handler = m_NativeSdkFactory.getHandler(className);
    QObject * item = NULL;
    if(handler){
        insertHandlerBase2List(handler);
        item =  handler->getUiSource(actionName);
    }
    return item;
}
