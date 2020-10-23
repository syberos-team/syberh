#ifndef PROJECT_CONFIG_P_H
#define PROJECT_CONFIG_P_H

#include <QJsonObject>

namespace NativeSdk {

class ProjectConfigPrivate
{
public:
    bool load();
    QString errorMessage();

    QString getString(const QString &key);
    QString getString(const QString &key, const QString &key2);

    bool getBool(const QString &key);
    bool getBool(const QString &key, const QString &key2);
private:
    QJsonValue getValue(const QString &key);
    QJsonValue getValue(const QString &key, const QString &key2);

    void setErrorMessage(const QString &msg);

    QJsonObject conf;
    QString errMsg;
};

}
#endif // PROJECT_CONFIG_P_H