#ifndef LOADQMLWIDGET_H
#define LOADQMLWIDGET_H
#include <QObject>
#include <QQuickItem>
#include <QQuickView>
#include <QQmlContext>

class LoadQmlWidget :public QObject{
    Q_OBJECT
public:
    LoadQmlWidget(QString parentPageName,QString parentName,QString type);
    ~LoadQmlWidget();
    void showWidget();
private:
    QQuickItem *m_pItem; ///< 控件指针
    QQuickItem *m_pContentColItem;  ///< 控件所属列表的指针
    QQmlContext *m_pRootContext;
    QQuickView *m_pViewer;
    QString m_type; /// 控件类型
private:
    QString getQmlPath(QString type);

};

#endif // LOADQMLWIDGET_H
