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

    virtual bool initialize(const QStringList &arguments, QString *errorString) = 0;
    virtual void extensionsInitialized() = 0;
    virtual bool delayedInitialize() { return false; }
    virtual ShutdownFlag aboutToShutdown() { return SynchronousShutdown; }
    virtual QObject *remoteCommand(const QStringList & /* options */,
                                   const QString & /* workingDirectory */,
                                   const QStringList & /* arguments */) { return nullptr; }
    virtual QVector<QObject *> createTestObjects() const;

    PluginSpec *pluginSpec() const;

    //插件接受JS SDK调用方法,需要实现该方法，处理插件逻辑
    virtual void invoke(QString callbackID, QString action, QVariantMap params) = 0;
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
    ~SignalManager();

    static SignalManager *instance();

signals:
    void success(QString callbackID, QVariant result);
    void failed(QString callbackID, QString errorCode,QString errorMsg);
    void progress(QString callbackID, const int totalLength, const int progress, const int status);
    void subscribe(QString handleName, QVariant result);

private:
    SignalManager();
};

}
#endif // IPLUGIN_H
