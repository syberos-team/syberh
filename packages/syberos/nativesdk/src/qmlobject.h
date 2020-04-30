#ifndef QMLOBJECT_H
#define QMLOBJECT_H

#include "nativesdk_global.h"

#include <QObject>
#include <QQuickItem>

namespace NativeSdk {

namespace Internal {
    class QmlObjectPrivate;
}

class NATIVESDK_EXPORT QmlObject : public QObject
{
    Q_OBJECT
public:
    enum Status { Null, Ready, Loading, Error };

    explicit QmlObject(QObject *parent = 0);
    ~QmlObject();
    /**
     * @brief 实例化qml组件
     * @param qml qml文件路径
     * @param parentItem 父级节点
     */
    void create(const QString &qml, QQuickItem *parentItem);
    /**
     * @brief 使用pageStack打开新页面
     * @param qml qml文件路径
     * @param parentItem 调用PageStack的域
     * @param properties 打开页面是为页面设置属性
     */
    void open(const QString &qml, QQuickItem *parentItem, const QVariantMap &properties);
    /**
     * @brief 使用pageStatck关闭最顶层页面
     * @param parentItem 调用PageStack的域
     */
    void close(QQuickItem *parentItem);
    /**
     * @brief 链接qml中的信号
     * @param signal qml中的信号
     * @param receiver 接受信号的对象
     * @param member 接受信号的槽函数或信号函数
     */
    void connectSignal(const char *signal, const QObject *receiver, const char *member);
    /**
     * @brief 取消qml中的所有信号链接
     */
    void disconnectSignals();
    /**
     * @brief 设置qml中的属性值
     * @param property 属性名
     * @param value 属性值
     */
    void setProperty(const QString &property, const QVariant &value);
    /**
     * @brief 调用qml中的js表达式
     * @param expression js表达式
     * @return js表达式有返回结果时返回调用结果，无返回时返回无效值
     */
    QVariant call(const QString &expression);
    /**
     * @brief 根据objectName属性，查找qml中的子节点
     * @param objectName 查找的子节点的objectName属性名
     * @return 返回找到的节点
     */
    QList<QQuickItem*> find(const QString &objectName);
    /**
     * @brief 获取qml组件对象，注意，若调用了destroy()该方法会返回空指针
     * @return qml组件对象或空指针
     */
    QQuickItem* quickItem();
    /**
     * @brief qml组件的状态，在qml实例化过程中发生变化
     * @return
     */
    Status status();
    /**
     * @brief 是否有错误
     * @return
     */
    bool hasError();
    /**
     * @brief 错误信息，需要注意，该函数调用一次后会清空错误信息
     * @return
     */
    QString errorMessage();
    /**
     * @brief 销毁qml组件
     */
    void destroy();

signals:
    /**
     * @brief 创建组件前，需要链接该信号，出发该信号后才可以调用组件的其他方法
     */
    void ready();

private slots:
    void statusChanged(QQmlComponent::Status status);

private:
    Internal::QmlObjectPrivate *d;
};

}
#endif // QMLOBJECT_H
