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
}

IPlugin::~IPlugin()
{
    delete d;
    d = nullptr;
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
    return SignalManager::instance();
}
// ========== IPlugin & ==========


// ========== SignalManager ^ ==========
static QMutex mutex;
static SignalManager *s = nullptr;

SignalManager::SignalManager()
{
}

SignalManager::~SignalManager()
{
    if(s != nullptr){
        delete s;
        s = nullptr;
    }
}

SignalManager *SignalManager::instance()
{
    if(s == nullptr){
        QMutexLocker locker(&mutex);
        if(s == nullptr){
            s = new SignalManager();
        }
    }
    return s;
}
// ========== SignalManager & ==========
