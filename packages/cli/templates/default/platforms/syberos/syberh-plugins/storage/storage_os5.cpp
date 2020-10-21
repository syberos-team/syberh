#include "storage.h"
#include <qdebug.h>
#include "util/log.h"
#include "framework/common/errorinfo.h"


using namespace NativeSdk;

Storage::Storage()
{
}

Storage::~Storage(){
}


void Storage::invoke(QString callbackId, QString actionName, QVariantMap params) {
    qDebug() << "callbackId:" << callbackId << "actionName:" << actionName << "params:" << params << endl;

    emit signalManager()->failed(callbackId.toLong(), ErrorInfo::InvalidCall, ErrorInfo::message(ErrorInfo::InvalidCall, "不支持的模块"));
}


void Storage::setItem(QString callbackId, QString key, QVariant value){
    Q_UNUSED(callbackId)
    Q_UNUSED(key)
    Q_UNUSED(value)
}


void Storage::getItem(QString callbackId, QString key){
    Q_UNUSED(callbackId)
    Q_UNUSED(key)
}

void Storage::removeItem(QString callbackId, QString key){
    Q_UNUSED(callbackId)
    Q_UNUSED(key)
}

void Storage::removeAll(QString callbackId){
    Q_UNUSED(callbackId)
}

void Storage::getAllKeys(QString callbackId){
    Q_UNUSED(callbackId)
}

bool Storage::checkKey(QString callbackId, QString key, bool sendFailSign){
    Q_UNUSED(callbackId)
    Q_UNUSED(key)
    Q_UNUSED(sendFailSign)
    return false;
}

