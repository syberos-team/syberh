#include "clipboard.h"

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

}
void Clipboard::setClipboardData(long callBackID, QVariantMap params){

    QString data = params.value("data").toString();
     QClipboard *clipboard = QApplication::clipboard();
     clipboard->setText(data);

     QVariantMap map;
     emit success(callBackID, map);
}

void Clipboard::getClipboardData(long callBackID, QVariantMap params){

     QClipboard *clipboard = QApplication::clipboard();
     QString data=clipboard->text();
     QVariantMap map;
     map.insert("data", data);

     emit success(callBackID, map);
}

