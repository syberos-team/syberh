#include "clipboard.h"
#include <QJsonArray>
#include <QJsonObject>

int Clipboard::typeId = qRegisterMetaType<Clipboard *>();
Clipboard::Clipboard(){}
Clipboard::~Clipboard(){}

void Clipboard::request(QString callBackID, QString actionName, QVariantMap params){

    if (actionName == "setClipboardData")
     {
        this->setClipboardData(callBackID.toLong(), params);
     }

    if (actionName == "getClipboardData")
    {
     this->getClipboardData(callBackID.toLong(), params);
    }
}

void Clipboard::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes){
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
}
void Clipboard::setClipboardData(long callBackID, QVariantMap params){
     QString data = params.value("data").toString();
     QClipboard *clipboard = QApplication::clipboard();
     clipboard->setText(data);

     QJsonObject jsonObject;
     jsonObject.insert("data", data);

     QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);
     emit success(callBackID, QVariant(jsonObject));
}

void Clipboard::getClipboardData(long callBackID, QVariantMap params){
    Q_UNUSED(params)

     QClipboard *clipboard = QApplication::clipboard();
     QString data = clipboard->text();
     QVariantMap map;
     map.insert("data", data);

     QJsonObject jsonObject;
     jsonObject.insert("data", data);

     QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);
     emit success(callBackID, QVariant(jsonObject));
}

