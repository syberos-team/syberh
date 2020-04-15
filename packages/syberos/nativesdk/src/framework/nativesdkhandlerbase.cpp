#include "nativesdkhandlerbase.h"

namespace NativeSdk {

NativeSdkHandlerBase::NativeSdkHandlerBase(){

}
NativeSdkHandlerBase::~NativeSdkHandlerBase(){

}
void NativeSdkHandlerBase::request(QString callbackID,QString actionName,QVariantMap params){
    Q_UNUSED(callbackID)
    Q_UNUSED(actionName)
    Q_UNUSED(params)

}

QObject * NativeSdkHandlerBase::getUiSource(QString actionName){
    Q_UNUSED(actionName)
    return NULL;

}
void NativeSdkHandlerBase::loadQml(QString parentPageName, QString parentName, QString type)
{
    Q_UNUSED(parentPageName)
    Q_UNUSED(parentName)
    Q_UNUSED(type)
}

QString NativeSdkHandlerBase::getNetworkConnectStatus(){
    return NetworkStatus::getInstance()->getNetworkConnectStatus();
}
bool NativeSdkHandlerBase::netWorkConnected(){
    bool bConnected = false;
    QString netWorkType = NetworkStatus::getInstance()->getNetworkConnectStatus();
    if(netWorkType == "cellular" || netWorkType == "wifi"){
         bConnected = true;
    }
    return bConnected;
}

}
