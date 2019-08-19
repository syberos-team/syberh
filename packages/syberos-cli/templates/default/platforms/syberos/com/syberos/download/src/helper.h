#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <cenvironment.h>
#include <QtNetwork>

class Helper : public QObject
{
    Q_OBJECT
public:
    static Helper* instance();

    Q_INVOKABLE QString getWebRootPath();
    Q_INVOKABLE QString getDataRootPath();
    Q_INVOKABLE QString getExternStorageRootPath();
    Q_INVOKABLE QString getInnerStorageRootPath();
    //文件是否存在
    Q_INVOKABLE bool exists(QString filePath);

    Q_INVOKABLE void downloadFile(QString id, QString url);

signals:
    void success(QString id, QString json);

public slots:
    void saveDownloadFile(QString url, QByteArray bytes);
    void downloadFileFailed(QNetworkReply::NetworkError errorCode, QString errorMessage);
private:
    explicit Helper(QObject *parent = 0);

    CEnvironment *env;
    QMap<QString,QString> urlIdMap;
};

#endif // HELPER_H
