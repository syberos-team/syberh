#ifndef PLUGINSPEC_P_H
#define PLUGINSPEC_P_H

#include "pluginspec.h"
#include "iplugin/iplugin.h"

#include <QJsonObject>
#include <QObject>
#include <QPluginLoader>
#include <QRegExp>
#include <QStringList>
#include <QVector>
#include <QXmlStreamReader>

namespace ExtensionSystem {

class IPlugin;
class PluginManager;

namespace Internal {

class EXTENSIONSYSTEM_EXPORT PluginSpecPrivate : public QObject{
    Q_OBJECT
public:
    PluginSpecPrivate(PluginSpec *spec);

    bool read(const QString &fileName);
    bool provides(const QString &pluginName, const QString &version) const;
    bool resolveDependencies(const QVector<PluginSpec *> &specs);
    bool loadLibrary();
    bool initializePlugin();
    bool initializeExtensions();
    bool delayedInitialize();
    IPlugin::ShutdownFlag stop();
    void kill();

    void setEnabledBySettings(bool value);
    void setEnabledByDefault(bool value);
    void setForceEnabled(bool value);
    void setForceDisabled(bool value);

    QPluginLoader loader;

    QString name;
    QString version;
    QString compatVersion;
    bool required = false;
    bool hiddenByDefault = false;
    bool experimental = false;
    bool enabledByDefault = true;
    QString vendor;
    QString copyright;
    QString license;
    QString description;
    QString url;
    QString category;
    QRegExp platformSpecification;
    QVector<PluginDependency> dependencies;
    QJsonObject metaData;
    bool enabledBySettings = true;
    bool enabledIndirectly = false;
    bool forceEnabled = false;
    bool forceDisabled = false;

    QString location;
    QString filePath;
    QStringList arguments;

    QHash<PluginDependency, PluginSpec *> dependencySpecs;
    PluginSpec::PluginArgumentDescriptions argumentDescriptions;
    IPlugin *plugin = nullptr;

    PluginSpec::State state = PluginSpec::Invalid;
    bool hasError = false;
    QString errorString;

    static bool isValidVersion(const QString &version);
    static int versionCompare(const QString &version1, const QString &version2);

    QVector<PluginSpec *> enableDependenciesIndirectly(bool enableTestDependencies = false);

    bool readMetaData(const QJsonObject &pluginMetaData);

private:
    PluginSpec *q;

    bool reportError(const QString &err);
    static const QRegExp &versionRegExp();

};
}
}


#endif // PLUGINSPEC_P_H
