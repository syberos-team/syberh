#include "clipboard.h"

int Clipboard::typeId = qRegisterMetaType<Clipboard *>();
Clipboard::Clipboard(){}
Clipboard::~Clipboard(){}

void Clipboard::request(QString callBackID, QString actionName, QVariantMap params)
{
     qDebug() << "--------------request" << callBackID;
  if (actionName == "setClipboardData")
  {
    this->setClipboardData(callBackID.toLong(), params);
  }


    if (actionName == "getClipboardData")
    {
     this->getClipboardData(callBackID.toLong(), params);
    }
}
void Clipboard::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes){}
void Clipboard::setClipboardData(long callBackID, QVariantMap params){

    QString data = params.value("data").toString();
     QClipboard *clipboard = QApplication::clipboard();
     clipboard->setText(data);
     qDebug() << "--------------setClipboardData"<<data;

     emit sucess(callBackID, QVariant(true));
}

void Clipboard::getClipboardData(long callBackID, QVariantMap params){

     QClipboard *clipboard = QApplication::clipboard();
     QString data=clipboard->text();
     qDebug() << "--------------getClipboardData"<<data;
      emit sucess(callBackID, QVariant(data));
}

