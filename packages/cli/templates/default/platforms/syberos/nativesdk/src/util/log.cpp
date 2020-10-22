#include "log.h"
#include <QDebug>
#include <QDateTime>
#include <QtGlobal>
#include <qlogging.h>
#include <QMutexLocker>
#include <stdio.h>
#include <qlogging.h>

namespace NativeSdk {

#define TIME_FMT "HH:mm:ss"

Log* Log::logger = NULL;

static QMap<Log::Level, QString> levelNameMap;
// qDebug 打印的日志级别，默认为info
static Log::Level qDebugLevel;
// 当前日志级别
static Log::Level currentLevel;

static QMutex mutex;

void changeQDebugLevel(Log::Level qDebugLev){
    mutex.lock();
    qDebugLevel = qDebugLev;
    mutex.unlock();
}

void output(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    Q_UNUSED(type);

    if(qDebugLevel < currentLevel){
        return;
    }

    // 当qml中打印日志时，按照qDebug日志级别打印
    if(QString::fromLocal8Bit(context.category) == "qml"){
        switch(type){
        case QtDebugMsg:
            changeQDebugLevel(Log::VERBOSE);
            break;
        case QtWarningMsg:
            changeQDebugLevel(Log::WARNING);
            break;
        case QtCriticalMsg:
            changeQDebugLevel(Log::ERROR);
            break;
        case QtFatalMsg:
            changeQDebugLevel(Log::ERROR);
            break;
        default:
            changeQDebugLevel(Log::INFO);
            break;
        }
    }

    QString levelName = Log::levelName(qDebugLevel);
    QString datetime = QDateTime::currentDateTime().toString(TIME_FMT);
    fprintf(stderr, "%4s | %s - [%5d] %s | %s\n",
            levelName.toLocal8Bit().constData(),
            datetime.toLocal8Bit().constData(),
            context.line,
            context.function,
            msg.toUtf8().constData());
    // 修改qDebug打印的日志级别为默认的info级别
    changeQDebugLevel(Log::INFO);
}




Log::Log(QObject *parent) : QObject(parent){
    // os 5.0暂时不使用自定义日志处理
    #if (QT_VERSION < QT_VERSION_CHECK(5, 12, 0))
    qInstallMessageHandler(output);
    #endif

    levelNameMap.insert(Log::VERBOSE, "VERB");
    levelNameMap.insert(Log::INFO, "INFO");
    levelNameMap.insert(Log::WARNING, "WARN");
    levelNameMap.insert(Log::ERROR, "ERR");

    currentLevel = Log::INFO;
    qDebugLevel = Log::INFO;
}

Log::~Log(){
    levelNameMap.clear();
    if(logger!=NULL){
        delete logger;
        logger = NULL;
    }
}

Log* Log::instance(){
    if(logger==NULL){
        logger = new Log();
    }
    return logger;
}

QString Log::levelName(Level level){
    return levelNameMap.value(level);
}

void Log::setLevel(Log::Level level){
    mutex.lock();
    currentLevel = level;
    mutex.unlock();
}

void Log::setLevel(const QString &level){
    if(level.isEmpty()){
        setLevel(Log::INFO);
        return;
    }
    QString lev = level.toLower();
    if(lev==LOG_VERBOSE){
        setLevel(Log::VERBOSE);
    }else if(lev==LOG_INFO){
        setLevel(Log::INFO);
    }else if(lev==LOG_WARN || lev==LOG_WARNING){
        setLevel(Log::WARNING);
    }else if(lev==LOG_ERROR){
        setLevel(Log::ERROR);
    }
}

bool Log::isVerboseEnabled(){
    return currentLevel >= Log::VERBOSE;
}

bool Log::isInfoEnabled(){
    return currentLevel >= Log::INFO;
}

bool Log::isWarningEnabled(){
    return currentLevel >= Log::WARNING;
}

bool Log::isErrorEnabled(){
    return currentLevel >= Log::ERROR;
}

QDebug Log::verbose(){
    return verbose(Log::DEFAULT);
}

QDebug Log::verbose(Color col){
    changeQDebugLevel(Log::VERBOSE);
    return color(col);
}

QDebug Log::info(){
    return info(Log::DEFAULT);
}

QDebug Log::info(Color col){
    changeQDebugLevel(Log::INFO);
    return color(col);
}

QDebug Log::warn(){
    return warn(Log::DEFAULT);
}

QDebug Log::warn(Color col){
    changeQDebugLevel(Log::WARNING);
    return color(col);
}

QDebug Log::error(){
    return error(Log::DEFAULT);
}

QDebug Log::error(Color col){
    changeQDebugLevel(Log::ERROR);
    return color(col);
}


QDebug Log::black(){
    return qDebug() << "\033[30m";
}

QDebug Log::red(){
    return qDebug() << "\033[31m";
}

QDebug Log::green(){
    return qDebug() << "\033[32m";
}

QDebug Log::yellow(){
    return qDebug() << "\033[33m";
}

QDebug Log::blue(){
    return qDebug() << "\033[34m";
}

QDebug Log::violet(){
    return qDebug() << "\033[35m";
}

QDebug Log::skyBlue(){
    return qDebug() << "\033[36m";
}

QDebug Log::white(){
    return qDebug() << "\033[37m";
}

QDebug Log::color(Color col){
    switch (col) {
    case BLACK:
        return black();
    case RED:
        return red();
    case GREEN:
        return green();
    case YELLOW:
        return yellow();
    case BLUE:
        return blue();
    case VIOLET:
        return violet();
    case SKY_BLUE:
        return skyBlue();
    case WHITE:
        return white();
    default:
        return qDebug();
    }
}

QDebug color(const QString &color){
    return qDebug() << color;
}

QDebug color(const char* color){
    return qDebug() << color;
}

const char* Log::end(){
    return "\033[0m";
}

}
