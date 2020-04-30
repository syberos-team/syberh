#ifndef QMLMANAGER_H
#define QMLMANAGER_H

#include "qmlobject.h"
#include "nativesdk_global.h"

#include <QObject>
#include <QQuickItem>

namespace NativeSdk {

class NATIVESDK_EXPORT QmlManager : public QObject
{
    Q_OBJECT
public:
    explicit QmlManager(QObject *parent = 0);
    /**
     * @brief 尝试从最顶层节点中获取initialPage属性中的Cpage对象，若最顶层没有initialPage属性则获取的是最顶层的对象
     * @return 根节点
     */
    QQuickItem* rootItem();
    /**
     * @brief 使用pageStack.currentPage获取当前显示的页面
     * @return 返回当前的页面，若未获取到返回空指针
     */
    QQuickItem* currentItem();
    /**
     * @brief 创建qml组件，该方法会调用rootItem()作为qml组件的父级节点
     * @param qml qml文件路径
     * @return qml映射对象
     */
    QmlObject* create(const QString &qml);
    /**
     * @brief 创建qml组件，将参数parentItem作为qml组件的父级节点
     * @param qml qml文件路径
     * @param parentItem 父级节点
     * @return qml映射对象
     */
    QmlObject* create(const QString &qml, QQuickItem *parentItem);
    /**
     * @brief 使用PageStack对象push qml页面，该方法会调用rootItem()作为调用PageStack的域
     * @param qml qml文件路径
     * @return qml映射对象
     */
    QmlObject* open(const QString &qml);
    /**
     * @brief 使用PageStack对象push qml页面，并为qml页面中的属性赋值，该方法会调用rootItem()作为调用PageStack的域
     * @param qml qml文件路径
     * @param properties qml页面中的属性值
     * @return qml映射对象
     */
    QmlObject* open(const QString &qml, const QVariantMap &properties);
    /**
     * @brief 使用PageStack对象push qml页面，使用参数parentItem作为调用PageStack的域
     * @param qml qml文件路径
     * @param parentItem 调用PageStack的域
     * @return qml映射对象
     */
    QmlObject* open(const QString &qml, QQuickItem *parentItem);
    /**
     * @brief 使用PageStack对象push qml页面，并为qml页面中的属性赋值，使用参数parentItem作为调用PageStack的域
     * @param qml qml文件路径
     * @param parentItem 调用PageStack的域
     * @param properties qml页面中的属性值
     * @return qml映射对象
     */
    QmlObject* open(const QString &qml, QQuickItem *parentItem, const QVariantMap &properties);
    /**
     * @brief 使用PageStack对象pop qml页面，与open()方法配对使用
     */
    void close(QmlObject *qmlObject);
    /**
     * @brief 绑定qml页面中的信号
     * @param qmlObject qml映射对象
     * @param signal qml中的信号，使用SIGNAL()宏生成
     * @param receiver 接受qml信号的对象
     * @param member 接受qml信号的对象中的槽函数或信号函数，使用SLOT()宏生成
     */
    void connectSignal(QmlObject *qmlObject, const char *signal,
                       const QObject *receiver, const char *member);
    /**
     * @brief 为qml页面中的属性赋值
     * @param qmlObject qml映射对象
     * @param property qml页面中的属性名
     * @param value 属性值
     */
    void setProperty(QmlObject *qmlObject, const QString &property, const QVariant &value);
    /**
     * @brief 调用qml页面中的js表达式或qml页面中的js函数，该方法会使用rootItem()作为域调用表达式
     * @param expression js表达式或函数
     * @return 返回调用结果，若函数或表达式没有返回则为Invalid
     */
    QVariant call(const QString &expression);
    /**
     * @brief 调用qml页面中的js表达式或qml页面中的js函数
     * @param qmlObject qml映射对象
     * @param expression js表达式或函数
     * @return 返回调用结果，若函数或表达式没有返回则为Invalid
     */
    QVariant call(QmlObject *qmlObject, const QString &expression);
    /**
     * @brief 调用qml页面中的js表达式或qml页面中的js函数
     * @param item qml组件对象
     * @param expression js表达式或函数
     * @return 返回调用结果，若函数或表达式没有返回则为Invalid
     */
    QVariant call(QQuickItem *item, const QString &expression);
    /**
     * @brief 销毁QmlObject中的qml组件对象，调用了该方法后不应该再调用QmlObject中的其他方法，可能会引发空指针调用
     * @param qmlObject qml映射对象
     */
    void destroy(QmlObject *qmlObject);

signals:
    /**
     * @brief 调用create()前应该链接该信号，组件创建完成后会触发该信号，该信号出发后才能进行组件的其他操作
     */
    void createReady();
    /**
     * @brief 该类中方法调用出现错误时发送该信号
     * @param message 错误信息
     */
    void error(QString message);
};

}
#endif // QMLMANAGER_H
