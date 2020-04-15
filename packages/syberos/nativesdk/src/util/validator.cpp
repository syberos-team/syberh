#include "validator.h"
#include <QRegExp>

namespace NativeSdk {

Validator::Validator(QObject *parent) : QObject(parent){

}


bool Validator::isHttpUrl(const QString &url){
    QRegExp pattern("^(http|https)://.+", Qt::CaseInsensitive);
    return pattern.exactMatch(url);
}

}
