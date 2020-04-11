#ifndef IPLUGIN_P_H
#define IPLUGIN_P_H

#include "iplugin.h"

namespace ExtensionSystem {

class PluginSpec;

namespace Internal {

class IPluginPrivate
{
public:
    PluginSpec *pluginSpec;
};

} // namespace Internal
} // namespace ExtensionSystem


#endif // IPLUGIN_P_H
