#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "extensionsystem_global.h"

#include <QObject>
#include <QReadWriteLock>
#include <QSet>
#include <QVector>

QT_BEGIN_NAMESPACE
class QTextStream;
class QSettings;
QT_END_NAMESPACE

namespace ExtensionSystem {
class IPlugin;
class PluginSpec;

namespace Internal { class PluginManagerPrivate; }


class EXTENSIONSYSTEM_EXPORT PluginManager : public QObject
{
    Q_OBJECT
public:
    static PluginManager *instance();

    PluginManager();
    ~PluginManager();

    // Object pool operations
    static void addObject(QObject *obj);
    static void removeObject(QObject *obj);
    static QVector<QObject *> allObjects();
    static QReadWriteLock *listLock();

    // This is useful for soft dependencies using pure interfaces.
    template <typename T> static T *getObject()
    {
        QReadLocker lock(listLock());
        QVector<QObject *> all = allObjects();
        foreach (QObject *obj, all) {
            if (T *result = qobject_cast<T *>(obj))
                return result;
        }
        return nullptr;
    }
    template <typename T, typename Predicate> static T *getObject(Predicate predicate)
    {
        QReadLocker lock(listLock());
        QVector<QObject *> all = allObjects();
        foreach (QObject *obj, all) {
            if (T *result = qobject_cast<T *>(obj))
                if (predicate(result))
                    return result;
        }
        return 0;
    }

    static QObject *getObjectByName(const QString &name);

    // Plugin operations
    static QVector<PluginSpec *> loadQueue();
    static void loadPlugins();
    static QStringList pluginPaths();
    static void setPluginPaths(const QStringList &paths);
    static QString pluginIID();
    static void setPluginIID(const QString &iid);
    static const QVector<PluginSpec *> plugins();
    static QHash<QString, QVector<PluginSpec *>> pluginCollections();
    static bool hasError();
    static const QStringList allErrors();
    static QSet<PluginSpec *> pluginsRequiringPlugin(PluginSpec *spec);
    static QSet<PluginSpec *> pluginsRequiredByPlugin(PluginSpec *spec);


    // Settings
    static void setSettings(QSettings *settings);
    static QSettings *settings();
    static void setGlobalSettings(QSettings *settings);
    static QSettings *globalSettings();
    static void writeSettings();

    // command line arguments
    static QStringList arguments();
    static bool parseOptions(const QStringList &args,
        const QMap<QString, bool> &appOptions,
        QMap<QString, QString> *foundAppOptions,
        QString *errorString);
    static void formatOptions(QTextStream &str, int optionIndentation, int descriptionIndentation);
    static void formatPluginOptions(QTextStream &str, int optionIndentation, int descriptionIndentation);
    static void formatPluginVersions(QTextStream &str);

    static QString serializedArguments();

    static bool testRunRequested();

    static void profilingReport(const char *what, const PluginSpec *spec = nullptr);

    static QString platformName();

    static bool isInitializationDone();

    void remoteArguments(const QString &serializedArguments, QObject *socket);
    void shutdown();

    QString systemInformation() const;

signals:
    void objectAdded(QObject *obj);
    void aboutToRemoveObject(QObject *obj);

    void pluginsChanged();
    void initializationDone();
    void testsFinished(int failedTests);

    friend class Internal::PluginManagerPrivate;

private:
    static PluginManager *q;
};
}
#endif // PLUGINMANAGER_H
