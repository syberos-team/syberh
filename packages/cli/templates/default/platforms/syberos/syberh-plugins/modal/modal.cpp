#include "modal.h"
#include "framework/common/errorinfo.h"

using namespace NativeSdk;

Modal::Modal()
{
}

bool Modal::initialize(const QStringList &arguments, QString *errorString)
{
    qDebug() << Q_FUNC_INFO << "## hello plugin(1)!!!" << "arguments: " << arguments << "errorString" << errorString;
    return true;
}

void Modal::extensionsInitialized()
{
    qDebug() << Q_FUNC_INFO << "## hello plugin(2)!!!";
}

bool Modal::delayedInitialize()
{
    qDebug() << Q_FUNC_INFO << "## hello plugin(3)!!!";
    return true;
}

void Modal::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    if (actionName == "alert") {
        alert(callbackID, params);
    } else if (actionName == "confirm") {
        confirm(callbackID, params);
    } else if (actionName == "prompt") {
        prompt(callbackID, params);
    } else if (actionName == "toast") {
        toast(callbackID, params);
    } else if (actionName == "gtoast") {
        gtoast(callbackID, params);
    }
}


void Modal::alert(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << callbackID << "params" << params;
    globalCallbackID = callbackID.toLong();

    QString title = params.value("title").toString();
    QString content = params.value("content").toString();
    QString icon = params.value("titleIcon").toString();
    QString confirmText = params.value("confirmText", "确定").toString();
    QString confirmColor = params.value("confirmColor", "#007aff").toString();

    if (content.isEmpty()) {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "content不能为空");
        return;
    }

    if (!title.isEmpty() && title.size() > 7) {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "标题最多7个汉字");
        return;
    }

    if (!confirmText.isEmpty() && confirmText.size() > 4) {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "按钮最多4个汉字");
        return;
    }


    alertQml = qmlManager.create("qrc:/qml/SAlert.qml");

    qmlManager.setProperty(alertQml, "titleText", title);
    qmlManager.setProperty(alertQml, "messageText", content);
    qmlManager.setProperty(alertQml, "icon", icon);
    qmlManager.setProperty(alertQml, "acceptedButtonText", confirmText);
    qmlManager.setProperty(alertQml, "acceptButtonColor", confirmColor);
    qmlManager.setProperty(alertQml, "rejectButtonVisible", false);

    qmlManager.connectSignal(alertQml, SIGNAL(accepted()), this, SLOT(alertSuccess()));

    qmlManager.call(alertQml, "show()");
}

void Modal::alertSuccess()
{
    signalManager()->success(globalCallbackID, "");
    qmlManager.destroy(alertQml);
    globalCallbackID = 0;
}

void Modal::confirm(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << callbackID << "params" << params;
    globalCallbackID = callbackID.toLong();

    QString title = params.value("title").toString();
    QString content = params.value("content").toString();
    QString icon = params.value("titleIcon").toString();
    QString confirmText = params.value("confirmText", "确定").toString();
    QString confirmColor = params.value("confirmColor", "#007aff").toString();
    QString cancelText = params.value("cancelText", "取消").toString();
    QString cancelColor = params.value("cancelColor", "#333333").toString();

    if (content.isEmpty()) {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "content不能为空");
        return;
    }

    if (!title.isEmpty() && title.size() > 7) {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "标题最多7个汉字");
        return;
    }

    if ((!confirmText.isEmpty() && confirmText.size() > 4) || (!cancelText.isEmpty() && cancelText.size() > 4)) {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "按钮最多4个汉字");
        return;
    }

    confirmQml = qmlManager.create("qrc:/qml/SConfirm.qml");

    qmlManager.setProperty(confirmQml, "titleText", title);
    qmlManager.setProperty(confirmQml, "messageText", content);
    qmlManager.setProperty(confirmQml, "icon", icon);
    qmlManager.setProperty(confirmQml, "acceptedButtonText", confirmText);
    qmlManager.setProperty(confirmQml, "acceptButtonColor", confirmColor);
    qmlManager.setProperty(confirmQml, "rejectButtonText", cancelText);
    qmlManager.setProperty(confirmQml, "rejectButtonColor", cancelColor);

    qmlManager.connectSignal(confirmQml, SIGNAL(accepted()), this, SLOT(confirmSuccess()));
    qmlManager.connectSignal(confirmQml, SIGNAL(rejected()), this, SLOT(confirmReject()));

    qmlManager.call(confirmQml, "show()");
}

void Modal::confirmSuccess()
{
    signalManager()->success(globalCallbackID, true);
    qmlManager.destroy(confirmQml);
    globalCallbackID = 0;
}

void Modal::confirmReject()
{
    signalManager()->success(globalCallbackID, false);
    qmlManager.destroy(confirmQml);
    globalCallbackID = 0;
}


void Modal::prompt(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << callbackID << "params" << params;
    globalCallbackID = callbackID.toLong();

    QString title = params.value("title").toString();
    QString confirmText = params.value("confirmText", "确定").toString();
    QString cancelText = params.value("cancelText", "取消").toString();

    if (!title.isEmpty() && title.size() > 7) {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "标题最多7个汉字");
        return;
    }

    if ((!confirmText.isEmpty() && confirmText.size() > 4) || (!cancelText.isEmpty() && cancelText.size() > 4)) {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "按钮最多4个汉字");
        return;
    }

    promptQml = qmlManager.create("qrc:/qml/SInputDialog.qml");

    qmlManager.setProperty(promptQml, "titleText", title);
    qmlManager.setProperty(promptQml, "acceptedButtonText", confirmText);
    qmlManager.setProperty(promptQml, "rejectButtonText", cancelText);

    qmlManager.connectSignal(promptQml, SIGNAL(inputAccepted(QVariant)), this, SLOT(promptAccepted(QVariant)));
    qmlManager.connectSignal(promptQml, SIGNAL(inputBack()), this, SLOT(promptCancel()));

    qmlManager.call(promptQml, "show()");
}

void Modal::promptAccepted(QVariant value)
{
    signalManager()->success(globalCallbackID, value);
    qmlManager.destroy(promptQml);
    globalCallbackID = 0;
}

void Modal::promptCancel()
{
    signalManager()->success(globalCallbackID, "");
    qmlManager.destroy(promptQml);
    globalCallbackID = 0;
}


void Modal::toast(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << callbackID << "params" << params;

    QString title = params.value("title").toString();
    QString icon = params.value("icon").toString();
    QString duration = params.value("duration").toString();

    if (title.isEmpty()) {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "提示的内容不能为空");
        return;
    }

    toastQml = qmlManager.create("qrc:/qml/SToast.qml", qmlManager.currentItem());

    //QQmlExpression exp(m_view->rootContext(), childItem, "show('"+ title + "','" + icon + "'," + duration +")");

    QVariant result = qmlManager.call(toastQml, "show('"+ title + "','" + icon + "','" + duration +"')");

    QString errorMsg = result.toString();

    if (errorMsg.isEmpty()) {
        signalManager()->success(callbackID.toLong(), "");
    } else {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, errorMsg);
    }
}


void Modal::gtoast(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << callbackID << "params" << params;

    QString title = params.value("title").toString();

    if (title.isEmpty()) {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, "提示的内容不能为空");
        return;
    }

    qmlManager.call(qmlManager.rootItem(), "gToast.requestToast('" + title + "')");

    signalManager()->success(callbackID.toLong(), "");
}
