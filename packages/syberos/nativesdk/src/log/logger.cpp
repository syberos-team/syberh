#include "logger.h"
#include "zlog/zlog.h"
#include "../helper.h"
#include "../framework/common/projectconfig.h"

#include <QDebug>
#include <QMutex>
#include <QFile>
#include <QDir>

namespace Log {

#define LOG_CONF "log.conf"
#define ZLOG_DEBUG_LOG "syberh_zlog.debug.log"
#define ZLOG_ERROR_LOG "syberh_zlog.error.log"
#define ZLOG_CATEGORY "syberh"

#define pathAppend(path1, path2) \
    (QString("%1/%2").arg(path1, path2))
#define pathLogAppend(path1, path2) \
    (QString("%1/log/%2").arg(path1, path2))

#define zlogConfigLog(file) \
    pathAppend(NativeSdk::Helper::instance()->getAppRootPath(), QString(file))
#define zlogProfileLog(file) \
    pathLogAppend(NativeSdk::Helper::instance()->getDataRootPath(), QString(file)).toStdString().c_str()
#define zlogOutDir() \
    pathAppend(NativeSdk::Helper::instance()->getDataRootPath(), QString("log"))

namespace Internal {

class LoggerPrivate {
public:
    LoggerPrivate(Logger::Level level,
               const char *file, size_t filelen,
               const char *func, size_t funclen,
               long line) 
               : m_level(level), 
                m_file(file), m_filelen(filelen),
                m_func(func), m_funclen(funclen),
                m_line(line) { }

    ~LoggerPrivate() 
    {
        if(!m_zlogConf.isEmpty()){
            m_zlogConf.clear();
        }
        if(!m_loadError.isEmpty()){
            m_loadError.clear();
        }
    }

    void initZlog();

    Logger::Level m_level = Logger::LV_INFO;
    const char *m_file;
    size_t m_filelen;
    const char *m_func;
    size_t m_funclen;
    long m_line;
private:
    bool loadConfig();

    QString m_zlogConf;
    QString m_loadError;
};

}   // namespace internal

static QMutex mutex;
static zlog_category_t *zlog_cat = nullptr;

static QString zlogCategory = ZLOG_CATEGORY;

// 检查是否已初始化日志系统
inline bool isInitialized()
{
    return zlog_cat != nullptr;
}

namespace Internal {

// ====== LoggerPrivate ======
bool LoggerPrivate::loadConfig()
{
    QString configPath = zlogConfigLog(LOG_CONF);
    if(configPath.isEmpty()){
        m_loadError = "can not found config: null";
        return false;
    }

    QFile file(configPath);
    if(!file.exists()){
        m_loadError = "can not found config: " + configPath;
        return false;
    }
    if(!file.open(QIODevice::ReadOnly)){
        m_loadError = "open config fail: " + file.errorString();
        return false;
    }
    QByteArray contentBytes = file.readAll();
    file.close();
    if(contentBytes.length() > 1){
        m_zlogConf = QString(contentBytes);
        return true;
    }
    m_loadError = "config content is empty: " + configPath;
    return false;
}

void LoggerPrivate::initZlog()
{
    if(isInitialized()){
        return;
    }
    QMutexLocker locker(&mutex);
    if(isInitialized()){
        return;
    }

    if(!loadConfig()){
        qWarning() << Q_FUNC_INFO << m_loadError;
        return;
    }

    // 创建日志目录
    QString outPath = zlogOutDir();
    QDir outDir(outPath);
    if(!outDir.exists()){
        outDir.mkdir(outPath);
    }

    // debug模式时，打开zlog调试日志
    NativeSdk::ProjectConfig *projectConfig = NativeSdk::ProjectConfig::instance();
    if(projectConfig->isDebug()){
        setenv("ZLOG_PROFILE_DEBUG", zlogProfileLog(ZLOG_DEBUG_LOG), 1);
    }
    setenv("ZLOG_PROFILE_ERROR", zlogProfileLog(ZLOG_ERROR_LOG), 1);

    // 初始化zlog
    int rs = zlog_init(m_zlogConf.toStdString().c_str());
    if(rs){
        qWarning() << Q_FUNC_INFO << "init zlog failed:" << strerror(errno);
        return;
    }

    zlog_cat = zlog_get_category(zlogCategory.toStdString().c_str());
    if(!zlog_cat){
        qWarning() << Q_FUNC_INFO << "get zlog category failed:" << strerror(errno);
        zlog_fini();
        return;
    }
}

}   // namespace internal

// ====== Logger ======

Logger::Logger(Level level,
               const char *file, size_t filelen,
               const char *func, size_t funclen,
               long line)
    : m_ts(&m_buffer, QIODevice::WriteOnly)
{
    m_ts.setCodec("utf-8");

    d = new Internal::LoggerPrivate(level, file, filelen, func, funclen, line);
    d->initZlog();
}

Logger::~Logger()
{
    end();
    delete d;
}


bool Logger::isDebugEnabled()
{
    return zlog_level_enabled(zlog_cat, ZLOG_LEVEL_DEBUG) != 0;
}

bool Logger::isInfoEnabled()
{
    return zlog_level_enabled(zlog_cat, ZLOG_LEVEL_INFO) != 0;
}

bool Logger::isWarningEnabled()
{
    return zlog_level_enabled(zlog_cat, ZLOG_LEVEL_WARN) != 0;
}

bool Logger::isErrorEnabled()
{
    return zlog_level_enabled(zlog_cat, ZLOG_LEVEL_ERROR) != 0;
}


void Logger::setCategory(const QString &category)
{
    if(isInitialized()){
        return;
    }
    zlogCategory = category;
}

void Logger::setCategory(const char *category)
{
    setCategory(QString(category));
}

void Logger::clean()
{
    if(zlog_cat == nullptr){
        return;
    }
    zlog_fini();
    zlog_cat = nullptr;
}



void Logger::end()
{
    if(!m_whetherToLog)
        return;

    zlog_level lv;
    switch (d->m_level) {
    case Logger::LV_DEBUG:
        lv = ZLOG_LEVEL_DEBUG;
        break;
    case Logger::LV_INFO:
        lv = ZLOG_LEVEL_INFO;
        break;
    case Logger::LV_WARN:
        lv = ZLOG_LEVEL_WARN;
        break;
    case Logger::LV_ERROR:
        lv = ZLOG_LEVEL_ERROR;
        break;
    default:
        lv = ZLOG_LEVEL_INFO;
        break;
    }

    zlog(zlog_cat, d->m_file, d->m_filelen, d->m_func, d->m_funclen, d->m_line, lv, \
         "%s", m_ts.readAll().toStdString().c_str());
}

void Logger::putUcs4(uint ucs4)
{
    if (ucs4 < 0x20) {
        m_ts << "\\x" << hex << ucs4 << reset;
    } else if (ucs4 < 0x80) {
        m_ts << char(ucs4);
    } else {
        if (ucs4 < 0x10000)
            m_ts << "\\u" << qSetFieldWidth(4);
        else
            m_ts << "\\U" << qSetFieldWidth(8);
        m_ts << hex << qSetPadChar(QLatin1Char('0')) << ucs4 << reset;
    }
}

}