#include "App_Workspace.h"
#include <QQmlContext>
#include <QDebug>
#include <qqml.h>
#include <QSplashScreen>

// 若编译时使用vendor，则include vendor中的，否则include syberh-framework
#ifdef USE_VENDOR
    #include "../vendor/syberh/framework/src/helper.h"
    #include "../vendor/syberh/framework/src/framework/nativesdkmanager.h"
    #include "../vendor/syberh/framework/src/framework/common/extendedconfig.h"
    #include "../vendor/syberh/framework/src/util/log.h"
    #include "../vendor/syberh/framework/src/package.h"
    #include "../vendor/syberh/framework/src/util/fileutil.h"
    #include "../vendor/syberh/framework/src/framework/common/errorinfo.h"
#else
    #include "../../../../../syberh-framework/src/helper.h"
    #include "../../../../../syberh-framework/src/framework/nativesdkmanager.h"
    #include "../../../../../syberh-framework/src/framework/common/extendedconfig.h"
    #include "../../../../../syberh-framework/src/util/log.h"
    #include "../../../../../syberh-framework/src/package.h"
    #include "../../../../../syberh-framework/src/util/fileutil.h"
    #include "../../../../../syberh-framework/src/framework/common/errorinfo.h"
#endif


App_Workspace::App_Workspace()
    : CWorkspace()
{
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

    m_view = SYBEROS::SyberosGuiCache::qQuickView();
    m_view->engine()->addImportPath("qrc:/");

    QObject::connect(m_view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));

    Helper *helper = Helper::instance();
    m_view->rootContext()->setContextProperty("helper", helper);


    NativeSdkManager * nativeSdkManager = NativeSdkManager::getInstance();
    m_view->rootContext()->setContextProperty("NativeSdkManager",nativeSdkManager);

    FileUtil * fileutil = new FileUtil;
    m_view->rootContext()->setContextProperty("fileutil",fileutil);

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
