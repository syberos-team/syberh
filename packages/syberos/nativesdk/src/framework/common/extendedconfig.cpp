#include "extendedconfig.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

namespace NativeSdk {

ExtendedConfig* ExtendedConfig::_instance = 0;

ExtendedConfig::ExtendedConfig(QObject *parent) : QObject(parent)
{
    config = new QVariantMap();
#ifdef EX_CONFIG
    init(QLatin1String(EX_CONFIG));
#endif
}

ExtendedConfig::~ExtendedConfig(){
    if(config!=NULL){
        config->clear();
        delete config;
    }
    delete _instance;
}

void ExtendedConfig::init(QLatin1String exCfg){
    QString exConfig = QString(exCfg);
    if(exConfig.isEmpty()){
        qDebug() << Q_FUNC_INFO << " EX_CONFIG is empty" << endl;
        return;
    }

    QByteArray exConfigBytes;
    bool ok;
    int len = exConfig.size();
    for(int i=0; i<len; i+=2){
        exConfigBytes.append(char(exConfig.mid(i,2).toUShort(&ok,16)));
    }

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(exConfigBytes, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qDebug() << Q_FUNC_INFO << " EX_CONFIG error:" << parseError.errorString() << endl;
        return;
    }
    QJsonObject json = doc.object();
    QVariantMap jsonMap = json.toVariantMap();

    config->clear();
    QVariantMap::const_iterator i;
    for(i = jsonMap.constBegin(); i!=jsonMap.constEnd(); ++i){
        config->insert(i.key(), i.value());
    }
    qDebug() << Q_FUNC_INFO << " >>>>" << *config << "<<<<" << endl;
}

ExtendedConfig* ExtendedConfig::instance(){
    if(!_instance){
        _instance = new ExtendedConfig();
    }
    return _instance;
}


QVariantMap* ExtendedConfig::getConfigs(){
    return config;
}

QVariant ExtendedConfig::get(const QString& key){
    return this->config->value(key);
}

QString ExtendedConfig::getString(const QString &key)
{
    QVariant val = this->config->value(key);
    if(val.isNull() || !val.isValid()){
        return QString();
    }
    return val.toString();
}

QString ExtendedConfig::getString(const QString &key, const QString &defaultValue)
{
    QString val = getString(key);
    if(val.isEmpty()){
        return defaultValue;
    }
    return val;
}

bool ExtendedConfig::getBool(const QString &key)
{
    QVariant val = this->config->value(key);
    if(val.isNull() || !val.isValid()){
        return false;
    }
    return val.toBool();
}

}
