#include "storage.h"
#include <qdebug.h>
#include <QJsonArray>
#include <QJsonObject>

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
    qDebug() << Q_FUNC_INFO << "callbackId:" << callbackId << "actionName:" << actionName << "params:" << params << endl;

    if (actionName=="setItem"){
        setItem(callbackId, params.value("key").toString(), params.value("value"));
    }else if(actionName=="getItem") {
        getItem(callbackId, params.value("key").toString());
    }else if(actionName=="removeItem"){
        removeItem(callbackId, params.value("key").toString());
    }else if(actionName=="getAllKeys"){
        getAllKeys(callbackId);
    }else {
        emit failed(callbackId.toLong(), 500, "Invalid call");
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
    if(key==""){
        emit failed(callbackId.toLong(), 500, "key is blank");
        return;
    }
    if(value.isNull() || !value.isValid()){
        emit failed(callbackId.toLong(), 500, "value is empty");
        return;
    }
    manager->setValue(key, value, CStorageBasic::PolicyAlways);
    QJsonObject json;
    json.insert("result", true);
    emit success(callbackId.toLong(), json);
}


void Storage::getItem(QString callbackId, QString key){
    if(key==""){
        emit failed(callbackId.toLong(), 500, "key is blank");
        return;
    }
    QVariant value = manager->value(key, CStorageBasic::PolicyAlways);
    QJsonObject json;
    json.insert("value", QJsonValue::fromVariant(value));
    emit success(callbackId.toLong(), json);
}

void Storage::removeItem(QString callbackId, QString key){
    if(key==""){
        emit failed(callbackId.toLong(), 500, "key is blank");
        return;
    }
    manager->remove(key);
    bool isRemoved = !manager->contains(key);
    QJsonObject json;
    json.insert("result", isRemoved);
    emit success(callbackId.toLong(), json);
}

void Storage::getAllKeys(QString callbackId){
    QStringList keys = manager->listAll();
    QJsonObject json;
    json.insert("keys", QJsonArray::fromStringList(keys));
    emit success(callbackId.toLong(), json);
}

