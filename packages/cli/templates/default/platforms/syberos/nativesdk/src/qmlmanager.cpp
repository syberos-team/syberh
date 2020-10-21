#include "qmlmanager.h"

#include <QQmlContext>
#include <QQmlExpression>
#include <SyberosGuiCache>

namespace NativeSdk {

QmlManager::QmlManager(QObject *parent) : QObject(parent)
{

}

QQuickItem *QmlManager::rootItem()
{
    QQuickView *m_view = SYBEROS::SyberosGuiCache::qQuickView();
    QQuickItem *root = m_view->rootObject();
    QVariant initialPage = root->property("initialPage");
    if(initialPage.isNull() || !initialPage.isValid()){
        return root;
    }
    return initialPage.value<QQuickItem*>();
}

QQuickItem *QmlManager::currentItem()
{
    QQuickView *m_view = SYBEROS::SyberosGuiCache::qQuickView();
    QQuickItem *root = m_view->rootObject();

    QVariant cpage = call(root, "pageStack.currentPage");
    if(cpage.isNull() || !cpage.isValid()){
        return nullptr;
    }
    return cpage.value<QQuickItem*>();
}

QmlObject* QmlManager::create(const QString &qml)
{
    QQuickItem *root = rootItem();
    return create(qml, root);
}

QmlObject* QmlManager::create(const QString &qml, QQuickItem *parentItem)
{
    QmlObject *qmlObject = new QmlObject(this);
    QObject::connect(qmlObject, SIGNAL(ready()), this, SIGNAL(createReady()));

    qmlObject->create(qml, parentItem);
    if(qmlObject->hasError()){
        emit error(qmlObject->errorMessage());
    }
    return qmlObject;
}

QmlObject *QmlManager::open(const QString &qml)
{
    QVariantMap properties;
    return open(qml, properties);
}

QmlObject *QmlManager::open(const QString &qml, const QVariantMap &properties)
{
    QQuickItem *root = rootItem();
    return open(qml, root, properties);
}

QmlObject *QmlManager::open(const QString &qml, QQuickItem *parentItem)
{
    QVariantMap properties;
    return open(qml, parentItem, properties);
}

QmlObject *QmlManager::open(const QString &qml, QQuickItem *parentItem, const QVariantMap &properties)
{
    QmlObject *qmlObject = new QmlObject(this);
    qmlObject->open(qml, parentItem, properties);
    if(qmlObject->hasError()){
        emit error(qmlObject->errorMessage());
    }
    return qmlObject;
}

void QmlManager::close(QmlObject *qmlObject)
{
    QQuickItem *root = rootItem();
    qmlObject->close(root);
    if(qmlObject->hasError()){
        emit error(qmlObject->errorMessage());
    }
}

void QmlManager::connectSignal(QmlObject *qmlObject, const char *signal, const QObject *receiver, const char *member)
{
    qmlObject->connectSignal(signal, receiver, member);
}

void QmlManager::setProperty(QmlObject *qmlObject, const QString &property, const QVariant &value)
{
    qmlObject->setProperty(property, value);
}

QVariant QmlManager::call(const QString &expression)
{
    QQuickItem *root = rootItem();
    return call(root, expression);
}

QVariant QmlManager::call(QmlObject *qmlObject, const QString &expression)
{
    QVariant result = qmlObject->call(expression);
    if(qmlObject->hasError()){
        emit error(qmlObject->errorMessage());
    }
    return result;
}

QVariant QmlManager::call(QQuickItem *item, const QString &expression)
{
    QQuickView *m_view = SYBEROS::SyberosGuiCache::qQuickView();

    QQmlExpression exp(m_view->rootContext(), item, expression);
    QVariant result = exp.evaluate();
    if(exp.hasError()){
        emit error(exp.error().toString());
    }
    return result;
}

void QmlManager::destroy(QmlObject *qmlObject)
{
    qmlObject->destroy();
    qmlObject->deleteLater();
}

}
