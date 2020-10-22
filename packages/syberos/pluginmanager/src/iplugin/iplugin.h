#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "iplugin_global.h"

#include <QObject>
#include <QVariantMap>
#include <QtPlugin>

namespace ExtensionSystem {

namespace Internal {
    class IPluginPrivate;
    class PluginSpecPrivate;
}

class PluginManager;
class PluginSpec;
class SignalManager;

class IPLUGIN_EXPORT IPlugin : public QObject
{
    Q_OBJECT
public:
    enum ShutdownFlag {
            SynchronousShutdown,
            AsynchronousShutdown
        };

    IPlugin();
    ~IPlugin() override;

    virtual bool initialize(const QStringList &arguments, QString *errorString);
    virtual void extensionsInitialized();
    virtual bool delayedInitialize() { return false; }
    virtual ShutdownFlag aboutToShutdown() { return SynchronousShutdown; }
    virtual QObject *remoteCommand(const QStringList & /* options */,
                                   const QString & /* workingDirectory */,
                                   const QStringList & /* arguments */) { return nullptr; }
    virtual QVector<QObject *> createTestObjects() const;

    PluginSpec *pluginSpec() const;

    // 调用invoke前调用该方法，该方法第一次被调用时会调用invokeInitialize()，之后再被调用时不再调用invokeInitialize()
    void beforeInvoke();
    // 调用invoke前的初始化工作，该方法只会被调用一次
    virtual void invokeInitialize();
    //插件接受JS SDK调用方法,需要实现该方法，处理插件逻辑
    virtual void invoke(QString callbackID, QString action, QVariantMap params);
    //信号管理类，通过该类来绑定插件中的信号
    SignalManager* signalManager();
signals:
    void asynchronousShutdownFinished();

private:
    Internal::IPluginPrivate *d;

    friend class Internal::PluginSpecPrivate;
};


class SignalManager : public QObject {
    Q_OBJECT
public:
    SignalManager();
    ~SignalManager();

signals:
    void success(long callbackID, QVariant result);
    void failed(long callbackID, long errorCode,QString errorMsg);
    void progress(long callbackID, const int totalLength, const int progress, const int status);
    void subscribe(QString handleName, QVariant result);

};

}
#endif // IPLUGIN_H
