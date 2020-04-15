#include "iplugin.h"
#include "iplugin_p.h"
#include "../pluginmanager.h"
#include "../pluginspec.h"

#include <QMutex>

using namespace ExtensionSystem;


// ========== IPlugin ^ ==========

IPlugin::IPlugin()
    : d(new Internal::IPluginPrivate())
{
    d->signalManager = new SignalManager();
}

IPlugin::~IPlugin()
{
    if(d->signalManager){
        delete d->signalManager;
        d->signalManager = nullptr;
    }
    delete d;
    d = nullptr;
}

bool IPlugin::initialize(const QStringList &arguments, QString *errorString) {
    Q_UNUSED(arguments);
    Q_UNUSED(errorString);
    return false;
}


void IPlugin::extensionsInitialized() {
}

QVector<QObject *> IPlugin::createTestObjects() const
{
    return {};
}

PluginSpec *IPlugin::pluginSpec() const
{
    return d->pluginSpec;
}

SignalManager *IPlugin::signalManager()
{
    return d->signalManager;
}
// ========== IPlugin & ==========


// ========== SignalManager ^ ==========
SignalManager::SignalManager()
{
}

SignalManager::~SignalManager()
{
    QObject::disconnect(this, 0, 0, 0);
}

// ========== SignalManager & ==========
