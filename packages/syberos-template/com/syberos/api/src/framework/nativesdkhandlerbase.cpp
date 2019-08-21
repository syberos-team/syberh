#include "nativesdkhandlerbase.h"

NativeSdkHandlerBase::NativeSdkHandlerBase(){

}
NativeSdkHandlerBase::~NativeSdkHandlerBase(){

}
void NativeSdkHandlerBase::request(QString callBackID,QString actionName,QVariantMap params){
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(params)

}
void NativeSdkHandlerBase::submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes){
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
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
