#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


#include "fileutils.h"
#include "hostosinfo.h"
#include "namevaluedictionary.h"
#include "namevalueitem.h"
#include "optional.h"

#include <QMap>
#include <QStringList>

#include <functional>

QT_FORWARD_DECLARE_CLASS(QDebug)
QT_FORWARD_DECLARE_CLASS(QProcessEnvironment)

namespace Utils {

class Environment final : public NameValueDictionary
{
public:
    using NameValueDictionary::NameValueDictionary;

    static Environment systemEnvironment();
    static void setupEnglishOutput(Environment *environment);
    static void setupEnglishOutput(QProcessEnvironment *environment);
    static void setupEnglishOutput(QStringList *environment);

    QProcessEnvironment toProcessEnvironment() const;

    void appendOrSet(const QString &key, const QString &value, const QString &sep = QString());
    void prependOrSet(const QString &key, const QString &value, const QString &sep = QString());

    void appendOrSetPath(const QString &value);
    void prependOrSetPath(const QString &value);

    void prependOrSetLibrarySearchPath(const QString &value);
    void prependOrSetLibrarySearchPaths(const QStringList &values);

    using PathFilter = std::function<bool(const FilePath &)>;
    FilePath searchInPath(const QString &executable,
                          const FilePathList &additionalDirs = FilePathList(),
                          const PathFilter &func = PathFilter()) const;
    FilePathList findAllInPath(const QString &executable,
                               const FilePathList &additionalDirs = FilePathList(),
                               const PathFilter &func = PathFilter()) const;

    FilePathList path() const;
    FilePathList pathListValue(const QString &varName) const;
    QStringList appendExeExtensions(const QString &executable) const;

    bool isSameExecutable(const QString &exe1, const QString &exe2) const;

    QString expandedValueForKey(const QString &key) const;
    QString expandVariables(const QString &input) const;
    FilePath expandVariables(const FilePath &input) const;
    QStringList expandVariables(const QStringList &input) const;

    static void modifySystemEnvironment(const EnvironmentItems &list); // use with care!!!

private:
    FilePath searchInDirectory(const QStringList &execs, const FilePath &directory,
                               QSet<FilePath> &alreadyChecked) const;
};

class EnvironmentProvider
{
public:
    QByteArray id;
    QString displayName;
    std::function<Environment()> environment;

    static void addProvider(EnvironmentProvider &&provider);
    static const QVector<EnvironmentProvider> providers();
    static optional<EnvironmentProvider> provider(const QByteArray &id);
};

} // namespace Utils


#endif // ENVIRONMENT_H
