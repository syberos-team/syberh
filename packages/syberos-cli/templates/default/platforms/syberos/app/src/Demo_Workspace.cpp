#include "Demo_Workspace.h"
#include "globalobject.h"
#include "helper.h"
#include "download.h"
#include <QQmlContext>
#include <QDebug>
#include <qqml.h>

Demo_Workspace::Demo_Workspace()
    : CWorkspace()
{
    m_view = SYBEROS::SyberosGuiCache::qQuickView();
    QObject::connect(m_view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));


    GlobalObject *global = new GlobalObject(this);
    m_view->rootContext()->setContextProperty("global", global);

    Helper *helper = Helper::instance();
    m_view->rootContext()->setContextProperty("helper", helper);

    Download *download = Download::instance();
    m_view->rootContext()->setContextProperty("Download", download);

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

