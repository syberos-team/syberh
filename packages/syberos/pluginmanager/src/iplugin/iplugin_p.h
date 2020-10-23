#ifndef IPLUGIN_P_H
#define IPLUGIN_P_H

#include "iplugin.h"

namespace ExtensionSystem {

class PluginSpec;
class SignalManager;

namespace Internal {

class IPluginPrivate
{
public:
    PluginSpec *pluginSpec;
    SignalManager *signalManager;
    bool isInvokeInitialized = false;
};

} // namespace Internal
} // namespace ExtensionSystem


#endif // IPLUGIN_P_H
