#include "validator.h"
#include <QRegExp>
#include <cnetworkmanager.h>

namespace NativeSdk {

Validator::Validator(QObject *parent) : QObject(parent){

}


bool Validator::isHttpUrl(const QString &url){
    QRegExp pattern("^(http|https)://.+", Qt::CaseInsensitive);
    return pattern.exactMatch(url);
}

bool Validator::isNetworkConnected() {
    CNetworkManager manager;
    return manager.isNetworkAvailable();
}

}
