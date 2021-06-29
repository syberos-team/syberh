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
    NetworkStatus::NetworkType networkType = NetworkStatus::getInstance()->getNetworkConnectType();
    return networkType != NetworkStatus::None;
}

QString Validator::getNetworkConnectStatus() {
    return NetworkStatus::getInstance()->getNetworkConnectStatus();
}

}
