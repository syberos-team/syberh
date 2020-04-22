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

}
