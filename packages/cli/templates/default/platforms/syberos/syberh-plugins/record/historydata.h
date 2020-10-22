#ifndef HISTORYDATA_H
#define HISTORYDATA_H

#include <QObject>
#include <QtPlugin>
#include <QSqlDatabase>

class HistoryData : public QObject
{
    Q_OBJECT

public:
    HistoryData();

    void insertMetadata(QString path,int size,int duration,QString created);
    void removeMetadata(QString path);
    void updateMetadata(QString path,int size,int duration);
    QJsonArray selectMetadata();

private :
    QSqlDatabase myConnection;

    bool createConnection();
    bool checkOrCreateDir(QString path);
    QString formatTime(int duration);
};

#endif // HISTORYDATA_H
