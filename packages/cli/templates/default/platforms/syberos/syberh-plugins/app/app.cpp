#include "app.h"
#include "framework/common/errorinfo.h"
#include "qmlmanager.h"
#include <SyberosGuiCache>

using namespace NativeSdk;

App::App()
{
}

void App::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    if (actionName == "setAppOrientation") {
        setAppOrientation(callbackID, params);
    }
}

void App::setAppOrientation(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "setAppOrientation****" << callbackID << params;

    QString curOrientation = params.value("orientation", "1").toString();

    QQuickView *m_view = SYBEROS::SyberosGuiCache::qQuickView();
    QList<QQuickItem*> webviews = m_view->findChildren<QQuickItem*>("webView");
    qDebug() << Q_FUNC_INFO << "webviews****" << webviews.size() <<webviews;

    QmlManager qmlManager;

    for (int i = webviews.size()-1; i >= 0; i--) {
        qDebug() << Q_FUNC_INFO << "webview index****" << i;
        qmlManager.call(webviews.at(i), "setPageOrientation(" + curOrientation + ")");
    }
    signalManager()->success(callbackID.toLong(), true);
}
