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
        NetworkError = 4000,
        //未知的错误
        UnknowError = 9999,
        //不合法的参数
        illegalParamError = 4035,
        //不合法的媒体文件类型
        illegalMediaTypeError = 4004,
        //无效的url
        invalidURLError = 4048,
        //系统错误
        systemError = 6002
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
