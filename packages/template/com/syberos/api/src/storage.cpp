#include "storage.h"
#include <qdebug.h>
#include <QJsonArray>
#include <QJsonObject>
#include "./util/log.h"
#include "./framework/common/errorinfo.h"

int Storage::typeId = qRegisterMetaType<Storage *>();

Storage::Storage()
{
    manager = CCryptoStorageManager::createCryptoStorageManager(CStorageBasic::CapabilityBasicOnly);
}

Storage::~Storage(){
    CCryptoStorageManager::freeCryptoStorageManager(manager);
    manager = 0;
}

void Storage::request(QString callbackId,QString actionName,QVariantMap params){
    qDebug() << "callbackId:" << callbackId << "actionName:" << actionName << "params:" << params << endl;

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
        emit failed(callbackId.toLong(), ErrorInfo::InvalidCall, ErrorInfo::message(ErrorInfo::InvalidCall, "方法不存在"));
    }
}

void Storage::submit(QString typeID,QString callbackId,QString actionName,QVariant dataRowList, QVariant attachementes){
    Q_UNUSED(typeID);
    Q_UNUSED(callbackId);
    Q_UNUSED(actionName);
    Q_UNUSED(dataRowList);
    Q_UNUSED(attachementes);
}

void Storage::setItem(QString callbackId, QString key, QVariant value){
    if(!checkKey(callbackId, key, true)){
        return;
    }
    if(value.isNull() || !value.isValid()){
        emit failed(callbackId.toLong(), ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "键值不能为空"));
        return;
    }
    manager->setValue(key, value, CStorageBasic::PolicyAlways);
    CStorageBasic::CryptoStorageStatus status = manager->status();
    qDebug() << Q_FUNC_INFO << "setItem status:" << status;

    QJsonObject json;
    json.insert("result", status==CStorageBasic::NoneError);
    emit success(callbackId.toLong(), json);
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
    emit success(callbackId.toLong(), json);
}

void Storage::removeItem(QString callbackId, QString key){
    if(!checkKey(callbackId, key, true)){
        return;
    }
    QJsonObject json;
    if(!manager->contains(key)){
        json.insert("result", false);
        emit success(callbackId.toLong(), json);
        return;
    }
    manager->remove(key);
    CStorageBasic::CryptoStorageStatus status = manager->status();
    qDebug() << Q_FUNC_INFO << "removeItem status:" << status;

    bool isRemoved = !manager->contains(key);
    json.insert("result", isRemoved);
    emit success(callbackId.toLong(), json);
}

void Storage::removeAll(QString callbackId){
    manager->removeAllOwnedKeys();
    CStorageBasic::CryptoStorageStatus status = manager->status();
    qDebug() << Q_FUNC_INFO << "removeAll status:" << status;
    QJsonObject json;
    json.insert("result", status==CStorageBasic::NoneError);
    emit success(callbackId.toLong(), json);
}

void Storage::getAllKeys(QString callbackId){
    QStringList keys = manager->listAll();
    CStorageBasic::CryptoStorageStatus status = manager->status();
    qDebug() << Q_FUNC_INFO << "getAllKeys status:" << status;

    QJsonObject json;
    json.insert("keys", QJsonArray::fromStringList(keys));
    emit success(callbackId.toLong(), json);
}

bool Storage::checkKey(QString callbackId, QString key, bool sendFailSign){
    if(key==""){
        if(sendFailSign){
            emit failed(callbackId.toLong(), ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "键名不能为空"));
        }
        return false;
    }
    qDebug() << Q_FUNC_INFO << "key length:" << key.length();
    if(key.length() > 40){
        if(sendFailSign){
            emit failed(callbackId.toLong(), ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "键名长度超长，最大长度40"));
        }
        return false;
    }
    return true;
}

