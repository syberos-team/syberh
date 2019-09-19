#include "App_Workspace.h"
#include <QQmlContext>
#include <QDebug>
#include <qqml.h>
#include <QSplashScreen>
#include "../com/syberos/api/src/helper.h"
#include "../com/syberos/api/src/framework/nativesdkmanager.h"
#include "../com/syberos/api/src/framework/common/extendedconfig.h"
#include "../com/syberos/api/src/url.h"

App_Workspace::App_Workspace()
    : CWorkspace()
{

    m_view = SYBEROS::SyberosGuiCache::qQuickView();
    m_view->engine()->addImportPath("qrc:/");

    QObject::connect(m_view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));

    Helper *helper = Helper::instance();
    m_view->rootContext()->setContextProperty("helper", helper);


    NativeSdkManager * nativeSdkManager = NativeSdkManager::getInstance();
    m_view->rootContext()->setContextProperty("NativeSdkManager",nativeSdkManager);
    m_view->setSource(QUrl("qrc:/qml/main.qml"));
    m_view->showFullScreen();

    m_root = (QObject *)(m_view->rootObject());

}

void App_Workspace::onLaunchComplete(Option option, const QStringList& params)
{
    Q_UNUSED(params)

    switch (option) {
    case CWorkspace::HOME:
        qDebug()<< "Start by Home";
        break;
    case CWorkspace::URL:
        break;
    case CWorkspace::EVENT:
        break;
    case CWorkspace::DOCUMENT:
        break;
    default:
        break;
    }
}

void App_Workspace::openByUrl(const QUrl& url){
    NativeSdkManager::getInstance()->url(url);
}

