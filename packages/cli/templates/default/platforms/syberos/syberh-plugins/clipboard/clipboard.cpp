#include "clipboard.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QClipboard>
#include <QApplication>
#include <QDebug>


Clipboard::Clipboard()
{
}

void Clipboard::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    if (actionName == "setClipboardData") {
        setClipboardData(callbackID, params);
    } else if (actionName == "getClipboardData") {
        getClipboardData(callbackID, params);
    }
}

void Clipboard::setClipboardData(QString callbackID, QVariantMap params){
    QString data = params.value("data").toString();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(data);

    QJsonObject jsonObject;
    jsonObject.insert("data", data);

    QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);
    signalManager()->success(callbackID.toLong(), QVariant(jsonObject));
}

void Clipboard::getClipboardData(QString callbackID, QVariantMap params){
    Q_UNUSED(params)

    QClipboard *clipboard = QApplication::clipboard();
    QString data = clipboard->text();
    QVariantMap map;
    map.insert("data", data);

    QJsonObject jsonObject;
    jsonObject.insert("data", data);

    QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);
    signalManager()->success(callbackID.toLong(), QVariant(jsonObject));
}

