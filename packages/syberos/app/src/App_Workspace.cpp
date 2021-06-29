#include "App_Workspace.h"
#include <QQmlContext>
#include <QDebug>
#include <qqml.h>
#include <QSplashScreen>
#include <cenvironment.h>
// QT版本大于5.6
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
#include <qtwebengineglobal.h>
#else
#include "../../nativesdk/src/senvironment.h"
#endif

#include "../../nativesdk/src/helper.h"
#include "../../nativesdk/src/framework/nativesdkmanager.h"
#include "../../nativesdk/src/framework/common/projectconfig.h"
#include "../../nativesdk/src/util/log.h"
#include "../../nativesdk/src/util/fileutil.h"
#include "../../nativesdk/src/framework/common/errorinfo.h"



using namespace NativeSdk;

App_Workspace::App_Workspace()
    : CWorkspace()
{
    ProjectConfig *projectConfig = ProjectConfig::instance();
    // 设置日志级别，若开启了debug将日志级别强制设为verbose
    QString logLevel = projectConfig->getLogLevel();
    bool debug = projectConfig->isDebug();
    if(debug){
        logLevel = LOG_VERBOSE;
    }
    Log::instance()->setLevel(logLevel);


    // 初始化错误信息
    ErrorInfo::init();

    // QT版本大于5.6， 开始支持webgl
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);

    // 开启 chromium devtools
    if(debug){
        QString devToolServer = QString("%1:%2").arg(projectConfig->getDeployIP()).arg(projectConfig->getDebuggingPort());
        qputenv("QTWEBENGINE_REMOTE_DEBUGGING", devToolServer.toLatin1());
        qDebug() << "QTWEBENGINE_REMOTE_DEBUGGING:" << devToolServer;
    }

    QtWebEngine::initialize();
    #endif

    m_view = SYBEROS::SyberosGuiCache::qQuickView();
    m_view->engine()->addImportPath("qrc:/");

    QObject::connect(m_view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));

    m_view->rootContext()->setContextProperty("projectConfig", projectConfig);
    Helper *helper = Helper::instance();
    m_view->rootContext()->setContextProperty("helper", helper);

    NativeSdkManager * nativeSdkManager = NativeSdkManager::getInstance();
    m_view->rootContext()->setContextProperty("NativeSdkManager",nativeSdkManager);

    FileUtil * fileutil = new FileUtil;
    m_view->rootContext()->setContextProperty("fileutil",fileutil);


    // 根据QT版本调用对应系统版本的main.qml
    #if (QT_VERSION < QT_VERSION_CHECK(5, 6, 0))
        SEnvironment *env = new SEnvironment;
        m_view->rootContext()->setContextProperty("env", env);
        m_view->setSource(QUrl("qrc:/qml/os2/main.qml"));
    #elif (QT_VERSION < QT_VERSION_CHECK(5, 12, 0))
        m_view->setSource(QUrl("qrc:/qml/os4/main.qml"));
    #else
        m_view->setSource(QUrl("qrc:/qml/os5/main.qml"));
    #endif

    m_view->showFullScreen();

}

void App_Workspace::onLaunchComplete(Option option, const QStringList& params)
{
    Q_UNUSED(params)

    switch (option) {
    case CWorkspace::HOME:
        qDebug()<< "Start by Home";
        break;
    case CWorkspace::URL:
        {
            QString urlStr = params.at(0);
            QUrl url(urlStr);
            NativeSdkManager::getInstance()->openByUrl(url);
        }
        break;
    case CWorkspace::EVENT:
        break;
    case CWorkspace::DOCUMENT:
        if(params.size() >= 3){
            QString action = params.at(0);
            QString mimetype = params.at(1);
            QString file = params.at(2);
            NativeSdkManager::getInstance()->openByDocument(action, mimetype, file);
        }
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

