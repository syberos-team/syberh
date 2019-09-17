"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var LogLevel;
(function (LogLevel) {
    LogLevel[LogLevel["error"] = 1] = "error";
    LogLevel[LogLevel["warn"] = 2] = "warn";
    LogLevel[LogLevel["info"] = 3] = "info";
    LogLevel[LogLevel["verbose"] = 4] = "verbose";
})(LogLevel = exports.LogLevel || (exports.LogLevel = {}));
class Logger {
    /**
     * 构造函数，初始化日志级别
     * @param logLevel 日志级别字符串，可为空，为空时使用info级别
     */
    constructor(logLevel = 'info') {
        this.level = this.logLevelName(logLevel ? logLevel.toLowerCase() : 'info');
        this.printFunction = this.defaultPrintFunction;
        this.dateFormatFunction = this.defaultDateFormatFunction;
    }
    /**
     * 字符串格式的日志级别转换成枚举类型
     * @param logLevel 日志级别，默认为info
     */
    logLevelName(logLevel = 'info') {
        switch (logLevel) {
            case 'error':
                return LogLevel.error;
            case 'warn':
                return LogLevel.warn;
            case 'info':
                return LogLevel.info;
            case 'verbose':
                return LogLevel.verbose;
            default:
                return LogLevel.info;
        }
    }
    /**
     * 获取用于打印的日志级别标识
     * @param level 日志级别
     */
    getLevelTag(level) {
        switch (level) {
            case LogLevel.error:
                return 'ERR ';
            case LogLevel.warn:
                return 'WARN';
            case LogLevel.info:
                return 'INFO';
            case LogLevel.verbose:
                return 'VERB';
        }
    }
    /**
     * 默认的格式打印函数
     * @param levelTag  级别tag，如：VERB、INFO、WARN、ERR
     * @param timestamp 时间，已格式化为字符串
     * @param message  日志的内容
     */
    defaultPrintFunction(levelTag, timestamp, message) {
        return `${levelTag} ${timestamp} | ${message}`;
    }
    /**
     * 默认的时间格式化函数
     * @param date 时间
     */
    defaultDateFormatFunction(date) {
        const hour = date.getHours();
        const min = date.getMinutes();
        const sec = date.getSeconds();
        let stampStr = '';
        stampStr += (hour < 10) ? ('0' + hour) : hour;
        stampStr += ':';
        stampStr += (min < 10) ? ('0' + min) : min;
        stampStr += ':';
        stampStr += (sec < 10) ? ('0' + sec) : sec;
        return stampStr;
    }
    /**
     * 设置日志级别，通常情况下由构造函数设置日志级别，而无需调用该方法
     * @param logLevel 日志级别
     */
    setLevel(logLevel) {
        this.level = this.logLevelName(logLevel);
    }
    /**
     * 获取当前设置的日志级别
     */
    getLevel() {
        return this.level;
    }
    /**
     * 重新设置格式化打印函数
     * @param printFunc 为空时使用默认的打印函数
     */
    setPrintFunction(printFunc) {
        if (printFunc) {
            this.printFunction = printFunc;
        }
    }
    /**
     * 重新设置时间格式化函数
     * @param dateFormatFunc 为空时使用默认的格式化函数
     */
    setDateFormatFunction(dateFormatFunc) {
        if (dateFormatFunc) {
            this.dateFormatFunction = dateFormatFunc;
        }
    }
    /**
     * 判断是否启用error级别
     */
    isErrorEnabled() {
        return this.isLevelEnabled(LogLevel.error);
    }
    /**
     * 判断是否启用warn级别
     */
    isWarnEnabled() {
        return this.isLevelEnabled(LogLevel.warn);
    }
    /**
     * 判断是否启用info级别
     */
    isInfoEnabled() {
        return this.isLevelEnabled(LogLevel.info);
    }
    /**
     * 判断是否启用verbose级别
     */
    isVerboseEnabled() {
        return this.isLevelEnabled(LogLevel.verbose);
    }
    isLevelEnabled(level) {
        return this.level >= level;
    }
    log(logLevel, message, ...args) {
        const timestamp = this.dateFormatFunction(new Date());
        const msg = this.printFunction(this.getLevelTag(logLevel), timestamp, message);
        console.log(msg, ...args);
    }
    /**
     * 打印error日志，支持格式化字符：%s, %d, %j
     * @param message
     * @param args
     */
    error(message, ...args) {
        if (this.isLevelEnabled(LogLevel.error)) {
            this.log(LogLevel.error, message, ...args);
        }
    }
    /**
     * 打印warn日志，支持格式化字符：%s, %d, %j
     * @param message
     * @param args
     */
    warn(message, ...args) {
        if (this.isLevelEnabled(LogLevel.warn)) {
            this.log(LogLevel.warn, message, ...args);
        }
    }
    /**
     * 打印info日志，支持格式化字符：%s, %d, %j
     * @param message
     * @param args
     */
    info(message, ...args) {
        if (this.isLevelEnabled(LogLevel.info)) {
            this.log(LogLevel.info, message, ...args);
        }
    }
    /**
     * 打印verbose日志，支持格式化字符：%s, %d, %j
     * @param message
     * @param args
     */
    verbose(message, ...args) {
        if (this.isLevelEnabled(LogLevel.verbose)) {
            this.log(LogLevel.verbose, message, ...args);
        }
    }
}
exports.log = new Logger(process.env.DEV_LOG || '');
exports.default = exports.log;
