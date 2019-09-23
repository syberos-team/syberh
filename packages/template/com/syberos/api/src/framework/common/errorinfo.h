#ifndef ERRORINFO_H
#define ERRORINFO_H
#include <QString>
#include<QObject>
#include <QMap>
class ErrorInfo :public QObject{
    Q_OBJECT
public:
    //错误码
    enum ErrorCode {
        //网络错误
        NetworkError = 400,
        //未知的错误
        UnknowError = 500
    };

    static void init();

    static QString getErrorMessage(ErrorInfo::ErrorCode code);

    ~ErrorInfo();
private:
    explicit ErrorInfo(QObject *parent = 0);
    ErrorInfo(const ErrorInfo &) Q_DECL_EQ_DELETE;
    ErrorInfo& operator=(ErrorInfo errorInfo) Q_DECL_EQ_DELETE;
};

#endif // ERRORINFO_H
