#ifndef ERRORINFO_H
#define ERRORINFO_H
#include <QString>
#include<QObject>
#include <QMap>
class ErrorInfo :public QObject{
    Q_OBJECT
#define NETWORK_ERROR    -1
public:
    ErrorInfo();
    ~ErrorInfo();
    static QMap<int,QString> m_errorCode;

};

#endif // ERRORINFO_H
