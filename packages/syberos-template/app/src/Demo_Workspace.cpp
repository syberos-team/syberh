#include "Demo_Workspace.h"
#include "../framework/nativesdkmanager.h"
#include <QQmlContext>
#include <QDebug>
#include <qqml.h>
#include "../com/syberos/download/src/helper.h"
#include "../framework/common/extendedconfig.h"
#include "../com/syberos/core/src/decodeworkspace.h"
#include "../com/syberos/core/src/qtcamerascan.h"

Demo_Workspace::Demo_Workspace()
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

    qmlRegisterType<DecodeWorkSpace>("com.syberos.decodeWorkSpace", 1, 0, "DecodeWorkSpace");
    QtCameraScan *camera = QtCameraScan::getInstance();
    qDebug() << "QtCameraScan *camera = QtCameraScan::getInstance() ok";
    QQmlEngine::setObjectOwnership(camera, QQmlEngine::CppOwnership);
    m_view->rootContext()->setContextProperty("QtCameraScan", camera);

    NativeSdkManager * nativeSdkManager = NativeSdkManager::getInstance();
    m_view->rootContext()->setContextProperty("NativeSdkManager",nativeSdkManager);
    m_view->setSource(QUrl("qrc:/qml/main.qml"));
    m_view->showFullScreen();
}

void Demo_Workspace::onLaunchComplete(Option option, const QStringList& params)
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

