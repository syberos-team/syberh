#include "loadqmlwidget.h"
#include "syberos-guicache.h"
#include <QQmlContext>
#include <QDebug>
LoadQmlWidget::LoadQmlWidget(QString parentPageName, QString parentName, QString type){
    Q_UNUSED(parentPageName)
    m_pViewer = SYBEROS::SyberosGuiCache::qQuickView();
    m_pRootContext = m_pViewer->rootContext();
    QQuickItem *rootItem = m_pViewer->rootObject();
    m_pContentColItem = rootItem->findChild<QQuickItem *>(parentName);
    m_type = type;
}
LoadQmlWidget::~LoadQmlWidget(){


}
void LoadQmlWidget::showWidget(){
    QQmlEngine *engine = m_pViewer->engine();
    QString qmlPath = getQmlPath(m_type);
    QQmlComponent component(engine, QUrl(qmlPath), QQmlComponent::PreferSynchronous);
    if(component.isError())
        qDebug() << "component error is  " << component.errors();
    QObject *obj = component.create(m_pRootContext);
    m_pItem = qobject_cast<QQuickItem *>(obj);
    m_pItem->setParentItem(m_pContentColItem);
    m_pItem->setProperty("strText","c++ load qml");
    m_pItem->setHeight(200);
}
QString LoadQmlWidget::getQmlPath(QString type){
    QString qmlPath = "";
    if(type.compare("test")){
        qmlPath =  "qrc:/com/syberos/download/qml/test.qml";
    }
    return qmlPath;
}
