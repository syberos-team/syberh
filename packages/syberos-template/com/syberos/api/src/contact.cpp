#include "contact.h"
#include <QDebug>
#include <QJsonObject>


int Contact::typeId = qRegisterMetaType<Contact *>();

Contact::Contact()
{
    ccontant = new CContactModel(this);
}

Contact::~Contact()
{

}

void Contact::request(QString callBackID, QString actionName, QVariantMap params)
{
  if (actionName == "pick")
  {
    pick(callBackID.toLong(), params);
  }

}
void Contact::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
}

void Contact::pick(long callbackId,QVariantMap params)
{
    qDebug() << "--xuejun--IdRole--" << this->ccontant->IdRole << endl;
    qDebug() << "--xuejun--FirstNameRole--" << this->ccontant->FirstNameRole << endl;
    qDebug() << "--xuejun--MiddleNameRole--" << this->ccontant->MiddleNameRole << endl;
    qDebug() << "--xuejun--LastNameRole--" << this->ccontant->LastNameRole << endl;
    qDebug() << "--xuejun--DisplayLabelRole--" << this->ccontant->DisplayLabelRole << endl;
    qDebug() << "--xuejun--TypeRole--" << this->ccontant->TypeRole << endl;
    qDebug() << "--xuejun--PhoneNumberRole--" << this->ccontant->PhoneNumberRole << endl;
    QJsonObject json;
    json.insert("value", "xuejun");
    emit success(callbackId, json);
}
