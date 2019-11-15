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
#include "../../vendor/syberh-framework/src/senvironment.h"
#endif

#include "../../vendor/syberh-framework/src/helper.h"
#include "../../vendor/syberh-framework/src/framework/nativesdkmanager.h"
#include "../../vendor/syberh-framework/src/framework/common/extendedconfig.h"
#include "../../vendor/syberh-framework/src/util/log.h"
#include "../../vendor/syberh-framework/src/package.h"
#include "../../vendor/syberh-framework/src/util/fileutil.h"
#include "../../vendor/syberh-framework/src/framework/common/errorinfo.h"


App_Workspace::App_Workspace()
    : CWorkspace()
{
    // 做qml适配用的
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    CEnvironment::initAppDpi(266);
#endif

    // 设置日志级别
    QString devLog = ExtendedConfig::instance()->get(EX_DEV_LOG).toString();
    if(devLog.isEmpty()){
      bool debug=  ExtendedConfig::instance()->get(EX_DEBUG).toBool();
      if(debug){
          devLog=LOG_VERBOSE;
      }
    }
    Log::instance()->setLevel(devLog);

    // 初始化错误信息
    ErrorInfo::init();

    // QT版本大于5.6， 开始支持webgl
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);

    QtWebEngine::initialize();
    #endif

    m_view = SYBEROS::SyberosGuiCache::qQuickView();
    m_view->engine()->addImportPath("qrc:/");

    QObject::connect(m_view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));

    Helper *helper = Helper::instance();
    m_view->rootContext()->setContextProperty("helper", helper);


    NativeSdkManager * nativeSdkManager = NativeSdkManager::getInstance();
    m_view->rootContext()->setContextProperty("NativeSdkManager",nativeSdkManager);

    FileUtil * fileutil = new FileUtil;
    m_view->rootContext()->setContextProperty("fileutil",fileutil);

    // QT版本大于5.6，选择进入特定的qml页面
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    m_view->setSource(QUrl("qrc:/qml/main59.qml"));
    #else
    SEnvironment *env = new SEnvironment;
    m_view->rootContext()->setContextProperty("env", env);
    m_view->setSource(QUrl("qrc:/qml/main.qml"));
    #endif

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
