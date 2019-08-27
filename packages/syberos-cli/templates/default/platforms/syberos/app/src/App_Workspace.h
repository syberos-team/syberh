#ifndef __DEMO_WORKSPACE__
#define __DEMO_WORKSPACE__

#include <QQuickView>
#include <QQuickWindow>
#include <QQmlEngine>
#include <QQmlComponent>
#include <SyberosGuiCache>
#include <cgui_application.h>
#include <cworkspace.h>


using namespace SYBEROS;

class App_Workspace : public CWorkspace
{
    Q_OBJECT

private:
    QQuickView *m_view;

public:
    App_Workspace();

    // 应用启动结束时，回调此函数。根据传入的option，应用可以区分启动的方式。
    void onLaunchComplete(Option option, const QStringList& params);

};


#endif //__DEMO_WORKSPACE__
