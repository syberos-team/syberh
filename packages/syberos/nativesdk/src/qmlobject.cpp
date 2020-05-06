#include "qmlobject.h"
#include "qmlobject_p.h"

#include <QQmlComponent>
#include <QQmlExpression>
#include <QQmlError>
#include <SyberosGuiCache>

namespace NativeSdk {

// ========== QmlObject ^ ==========
static QmlObject::Status toStatus(QQmlComponent::Status status){
    int statusInt = status;
    return static_cast<QmlObject::Status>(statusInt);
}


QmlObject::QmlObject(QObject *parent) : QObject(parent)
{
    d = new Internal::QmlObjectPrivate(parent);
}

QmlObject::~QmlObject()
{
    if(d != nullptr){
        delete d;
    }
}

void QmlObject::create(const QString &qml, QQuickItem *parentItem)
{
    QQuickView *m_view = SYBEROS::SyberosGuiCache::qQuickView();

    // 必须加QUrl() 为了在os2.1上兼容(alert方法找不到路径会报错)
    QQmlComponent component(m_view->engine(), QUrl(qml));

    QObject::connect(&component, SIGNAL(statusChanged(QQmlComponent::Status)), this, SLOT(statusChanged(QQmlComponent::Status)));

    QQuickItem *childItem = qobject_cast<QQuickItem*>(component.beginCreate(m_view->rootContext()));
    childItem->setParentItem(parentItem);
    component.completeCreate();

    d->qmlItem = childItem;
    d->parentItem = parentItem;
    d->status = toStatus(component.status());
    d->errorMessage = component.errorString();
}

void QmlObject::open(const QString &qml, QQuickItem *parentItem, const QVariantMap &properties)
{
    QQuickView *m_view = SYBEROS::SyberosGuiCache::qQuickView();

    QJsonDocument json(QJsonObject::fromVariantMap(properties));
    QString jsonString(json.toJson());

    QString expression = QString("pageStack.push('%1', %2, false)").arg(qml).arg(jsonString);

    QQmlExpression exp(m_view->rootContext(), parentItem, expression);
    QVariant result = exp.evaluate();
    if(exp.hasError()){
        d->status = Error;
        d->errorMessage = exp.error().toString();
        return;
    }
    QQuickItem *childItem = result.value<QQuickItem*>();

    d->qmlItem = childItem;
    d->parentItem = parentItem;
    d->status = Ready;
    d->errorMessage = QString();
    emit ready();
}

void QmlObject::close(QQuickItem *parentItem)
{
    QQuickView *m_view = SYBEROS::SyberosGuiCache::qQuickView();
    QQmlExpression exp(m_view->rootContext(), parentItem, "pageStack.pop()");
    exp.evaluate();
    if(exp.hasError()){
        d->status = Error;
        d->errorMessage = exp.error().toString();
    }
}

void QmlObject::connectSignal(const char *signal, const QObject *receiver, const char *member)
{
    QObject::connect(d->qmlItem, signal, receiver, member);
}

void QmlObject::disconnectSignals()
{
    QObject::disconnect(d->qmlItem, 0, 0, 0);
}

void QmlObject::setProperty(const QString &property, const QVariant &value)
{
    d->qmlItem->setProperty(property.toLatin1().data(), value);
}

QVariant QmlObject::call(const QString &expression)
{
    QQuickView *m_view = SYBEROS::SyberosGuiCache::qQuickView();

    QQmlExpression exp(m_view->rootContext(), d->qmlItem, expression);
    QVariant result = exp.evaluate();
    if(exp.hasError()){
        d->errorMessage = exp.error().toString();
    }
    return result;
}

QList<QQuickItem *> QmlObject::find(const QString &objectName)
{
    return d->qmlItem->findChildren<QQuickItem*>(objectName);
}

QQuickItem *QmlObject::quickItem()
{
    return d->qmlItem;
}

QmlObject::Status QmlObject::status()
{
    return d->status;
}

bool QmlObject::hasError()
{
    return !(d->errorMessage.isEmpty());
}

QString QmlObject::errorMessage()
{
    QString err = d->errorMessage;
    d->errorMessage = QString();
    return err;
}

void QmlObject::destroy()
{
    if(d->qmlItem != nullptr){
        d->qmlItem->deleteLater();
        d->qmlItem = nullptr;
        d->parentItem = nullptr;
    }
}

void QmlObject::statusChanged(QQmlComponent::Status status)
{
    d->status = toStatus(status);
    if(d->status == Ready){
        emit ready();
    }
}
// ========== QmlObject & ==========


// ========== QmlObjectPrivate ^ ==========
namespace Internal {

QmlObjectPrivate::QmlObjectPrivate(QObject *parent) : QObject(parent)
{
}

}
// ========== QmlObjectPrivate & ==========

}
