#include "filepicker.h"
#include "helper.h"
#include "framework/common/errorinfo.h"
#include <QJsonDocument>
#include <QJsonArray>


Filepicker::Filepicker()
{
}

void Filepicker::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    if (actionName == "open") {
        open(callbackID, params);
    }
}

void Filepicker::open(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "params" << params;
    globalCallbackID = callbackID.toLong();

    QString title = params.value("title").toString();
    bool showBack = params.value("showBack", false).toBool();
    QString category = params.value("category", "all").toString();
    int count = params.value("count", 1).toInt();

    filepickerQml = qmlManager.open("qrc:/qml/SFilesPicker.qml");

    qmlManager.setProperty(filepickerQml, "titleText", title);
    qmlManager.setProperty(filepickerQml, "leftItemEnabled", showBack);
    qmlManager.setProperty(filepickerQml, "categoryType", category);
    qmlManager.setProperty(filepickerQml, "count", count);

    qmlManager.connectSignal(filepickerQml, SIGNAL(ok(QString)), this, SLOT(chooseOk(QString)));
    qmlManager.connectSignal(filepickerQml, SIGNAL(cancel()), this, SLOT(chooseCancel()));
}

void Filepicker::chooseOk(QString filesPath)
{
    // js传递json字符串过来
    qDebug() << Q_FUNC_INFO << "filesPath" << filesPath;

    QJsonDocument jsonDocument = QJsonDocument::fromJson(filesPath.toUtf8());
    if (jsonDocument.isNull()) {
        qDebug()<< "===> please check the string "<< filesPath.toLocal8Bit().data();
        signalManager()->failed(globalCallbackID, ErrorInfo::PluginError, "返回数据格式错误");
    }

    // json字符串转换为QJsonArray
    QJsonObject result = jsonDocument.object();

    qDebug() << Q_FUNC_INFO << "result***************" << result;

    signalManager()->success(globalCallbackID, QVariant(result));
    globalCallbackID = 0;

    qmlManager.close(filepickerQml);
}

void Filepicker::chooseCancel()
{
    qDebug() << Q_FUNC_INFO;
    signalManager()->success(globalCallbackID, "");
    globalCallbackID = 0;
    qmlManager.close(filepickerQml);
}
