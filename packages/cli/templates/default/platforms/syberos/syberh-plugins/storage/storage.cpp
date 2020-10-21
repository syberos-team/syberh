#include "storage.h"
#include <qdebug.h>
#include <QJsonArray>
#include <QJsonObject>
#include "util/log.h"
#include "framework/common/errorinfo.h"
#include <ccryptostoragemanager.h>

using namespace NativeSdk;

static CCryptoStorageManager* manager = nullptr;

Storage::Storage()
{
}

Storage::~Storage(){
}


void Storage::invoke(QString callbackId, QString actionName, QVariantMap params) {
    qDebug() << "callbackId:" << callbackId << "actionName:" << actionName << "params:" << params << endl;

    if (manager == nullptr){
        manager = CCryptoStorageManager::createCryptoStorageManager(CStorageBasic::CapabilityBasicOnly);
    }
    if (actionName=="setItem"){
        setItem(callbackId, params.value("key").toString(), params.value("value"));
    }else if(actionName=="getItem") {
        getItem(callbackId, params.value("key").toString());
    }else if(actionName=="removeItem"){
        removeItem(callbackId, params.value("key").toString());
    }else if(actionName=="getAllKeys"){
        getAllKeys(callbackId);
    }else if(actionName=="removeAll"){
        removeAll(callbackId);
    }else {
        emit signalManager()->failed(callbackId.toLong(), ErrorInfo::InvalidCall, ErrorInfo::message(ErrorInfo::InvalidCall, "方法不存在"));
    }
    if (manager != nullptr){
        CCryptoStorageManager::freeCryptoStorageManager(manager);
        manager = nullptr;
    }
}


void Storage::setItem(QString callbackId, QString key, QVariant value){
    if(!checkKey(callbackId, key, true)){
        return;
    }
    if(value.isNull() || !value.isValid()){
        emit signalManager()->failed(callbackId.toLong(), ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "键值不能为空"));
        return;
    }
    manager->setValue(key, value, CStorageBasic::PolicyAlways);
    CStorageBasic::CryptoStorageStatus status = manager->status();
    qDebug() << Q_FUNC_INFO << "setItem status:" << status;

    QJsonObject json;
    json.insert("result", status==CStorageBasic::NoneError);
    emit signalManager()->success(callbackId.toLong(), json);
}


void Storage::getItem(QString callbackId, QString key){
    if(!checkKey(callbackId, key, true)){
        return;
    }
    QVariant value = manager->value(key, CStorageBasic::PolicyAlways);
    CStorageBasic::CryptoStorageStatus status = manager->status();
    qDebug() << Q_FUNC_INFO << "getItem status:" << status;

    QJsonObject json;
    json.insert("value", QJsonValue::fromVariant(value));
    emit signalManager()->success(callbackId.toLong(), json);
}

void Storage::removeItem(QString callbackId, QString key){
    if(!checkKey(callbackId, key, true)){
        return;
    }
    QJsonObject json;
    if(!manager->contains(key)){
        json.insert("result", false);
        emit signalManager()->success(callbackId.toLong(), json);
        return;
    }
    manager->remove(key);
    CStorageBasic::CryptoStorageStatus status = manager->status();
    qDebug() << Q_FUNC_INFO << "removeItem status:" << status;

    bool isRemoved = !manager->contains(key);
    json.insert("result", isRemoved);
    emit signalManager()->success(callbackId.toLong(), json);
}

void Storage::removeAll(QString callbackId){
    manager->removeAllOwnedKeys();
    CStorageBasic::CryptoStorageStatus status = manager->status();
    qDebug() << Q_FUNC_INFO << "removeAll status:" << status;
    QJsonObject json;
    json.insert("result", status==CStorageBasic::NoneError);
    emit signalManager()->success(callbackId.toLong(), json);
}

void Storage::getAllKeys(QString callbackId){
    QStringList keys = manager->listAll();
    CStorageBasic::CryptoStorageStatus status = manager->status();
    qDebug() << Q_FUNC_INFO << "getAllKeys status:" << status;

    QJsonObject json;
    json.insert("keys", QJsonArray::fromStringList(keys));
    emit signalManager()->success(callbackId.toLong(), json);
}

bool Storage::checkKey(QString callbackId, QString key, bool sendFailSign){
    if(key.isEmpty()){
        if(sendFailSign){
            emit signalManager()->failed(callbackId.toLong(), ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "键名不能为空"));
        }
        return false;
    }
    qDebug() << Q_FUNC_INFO << "key length:" << key.length();
    if(key.length() > 40){
        if(sendFailSign){
            emit signalManager()->failed(callbackId.toLong(), ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "键名长度超长，最大长度40"));
        }
        return false;
    }
    return true;
}

