#ifndef HISTORYDATA_H
#define HISTORYDATA_H

#include <QSqlQueryModel>

#include "framework/nativesdkhandlerbase.h"
class HistoryData : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE HistoryData();
    ~HistoryData();

    void request(QString callBackID,QString actionName,QVariantMap params);
    void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);

    void insertMetadata(QString path,int size,int duration,QString created);
    void removeMetadata(QString path);
    void updateMetadata(QString path,int size,int duration);
    QJsonArray selectMetadata();

private :
    static int typeId;
    QSqlDatabase myConnection;

    bool createConnection();
    bool checkOrCreateDir(QString path);
    QString formatTime(int duration);

};
#endif // HISTORYDATA_H
