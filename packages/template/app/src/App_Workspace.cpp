#include "App_Workspace.h"
#include "../com/syberos/api/src/framework/nativesdkmanager.h"
#include <QQmlContext>
#include <QDebug>
#include <qqml.h>
#include "../com/syberos/api/src/helper.h"
#include "../com/syberos/api/src/framework/common/extendedconfig.h"
#include "../com/syberos/api/src/package.h"

App_Workspace::App_Workspace()
    : CWorkspace()
{

//    QVariant appName = ExtendedConfig::instance()->get("appName");
//    if(appName.isValid()){
//        qDebug() << "||||||||||||||| has appName" << appName << endl;
//    }else{
//        qDebug() << "||||||||||||||| no appName" << appName << endl;
//    }


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
    NativeSdkManager::getInstance()->openByUrl(url);
}

void App_Workspace::openByDocument(const QString& action, const QString& mimetype, const QString& file){

    NativeSdkManager::getInstance()->openByDocument(action, mimetype, file);
}
