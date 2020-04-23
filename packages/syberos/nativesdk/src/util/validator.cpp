#include "validator.h"
#include "../framework/common/networkstatus.h"
#include <QRegExp>

namespace NativeSdk {

Validator::Validator(QObject *parent) : QObject(parent){

}


bool Validator::isHttpUrl(const QString &url){
    QRegExp pattern("^(http|https)://.+", Qt::CaseInsensitive);
    return pattern.exactMatch(url);
}

bool Validator::netWorkConnected() {
    bool bConnected = false;
    QString netWorkType = NetworkStatus::getInstance()->getNetworkConnectStatus();
    if(netWorkType == "cellular" || netWorkType == "wifi"){
         bConnected = true;
    }
    return bConnected;
}

QString Validator::getNetworkConnectStatus() {
    return NetworkStatus::getInstance()->getNetworkConnectStatus();
}

}
