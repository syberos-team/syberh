#include "nativesdkhandlerbase.h"

namespace NativeSdk {

NativeSdkHandlerBase::NativeSdkHandlerBase(){

}
NativeSdkHandlerBase::~NativeSdkHandlerBase(){

}
void NativeSdkHandlerBase::request(const QString &callbackID, const QString &actionName, const QVariantMap &params){
    Q_UNUSED(callbackID)
    Q_UNUSED(actionName)
    Q_UNUSED(params)
}

}
