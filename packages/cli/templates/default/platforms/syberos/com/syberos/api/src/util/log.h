#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QDateTime>

#define LOG_VERBOSE "verbose"
#define LOG_INFO "info"
#define LOG_WARN "warn"
#define LOG_WARNING "warning"
#define LOG_ERROR "error"

class Log : public QObject
{
    Q_OBJECT
public:
    enum Level {
        VERBOSE = 1,
        INFO,
        WARNING,
        ERROR
    };

    ~Log();

    static Log* instance();
    /**
     * @brief levelName 根据日志级别获取到打印时的级别名
     * @param level 日志级别
     * @return 打印时的级别名，如：VERB、INFO、WARN、ERR
     */
    static QString levelName(Level level);
    /**
     * @brief setLevel 设置当前日志打印级别，高于或等于该级别的日志将会打印
     * @param level 日志级别
     */
    void setLevel(Log::Level level);
    /**
     * @brief setLevel 设置当前日志级别，高于或等于该级别的日志将会打印
     * @param level 日志级别：verbose、info、warn、error
     */
    void setLevel(const QString &level);

    bool isVerboseEnabled();
    bool isInfoEnabled();
    bool isWarningEnabled();
    bool isErrorEnabled();

    QDebug verbose();
    QDebug info();
    QDebug warn();
    QDebug error();

    QDebug black();
    QDebug red();
    QDebug green();
    QDebug yellow();
    QDebug blue();
    QDebug violet();
    QDebug skyBlue();
    QDebug white();

    const char* end();

private:
    explicit Log(QObject *parent = 0);
    Log(const Log &) Q_DECL_EQ_DELETE;
    Log& operator=(Log log) Q_DECL_EQ_DELETE;

    static Log* logger;
};

#endif // LOG_H
