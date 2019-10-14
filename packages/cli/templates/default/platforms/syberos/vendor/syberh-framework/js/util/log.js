/* eslint-disable no-unused-vars */
/* eslint-disable no-undef */

var logger = new Logger()

/**
 * 日志工具类
 */
function Logger () {
  this.levelName = helper.logLevelName() ? helper.logLevelName() : 'info'

  var LogLevel = {}
  LogLevel.error = 1
  LogLevel.warn = 2
  LogLevel.info = 3
  LogLevel.verbose = 4
  /**
   * 获取用于打印的日志级别标识
   * @param level 日志级别
   */
  function getLevelTag (level) {
    switch (level) {
      case LogLevel.error:
        return 'ERR '
      case LogLevel.warn:
        return 'WARN'
      case LogLevel.info:
        return 'INFO'
      case LogLevel.verbose:
        return 'VERB'
    }
  }

  function sprintf () {
    var args = arguments
    var text = args[0]
    var res = []
    var i = 1
    var rtext = text.replace(/%((%)|s|d)/g, function (m) {
      // m is the matched format, e.g. %s, %d
      var val = null
      if (m[2]) {
        val = m[2]
      } else {
        val = args[i]
        // A switch statement so that the formatter can be extended. Default is %s
        switch (m) {
          case '%d':
            val = parseFloat(val)
            if (isNaN(val)) {
              val = 0
            }
            break
        }
        i++
      }
      return val
    })
    if (rtext) {
      res.push(rtext)
    }
    // 处理剩余参数
    for (var s = i; s < arguments.length; s++) {
      res.push(arguments[s])
    }

    return res
  }

  /**
    * 字符串格式的日志级别转换成枚举类型
    * @param logLevel 日志级别，默认为info
    */
  function logLevelName (logLevel) {
    switch (logLevel) {
      case 'error':
        return LogLevel.error
      case 'warn':
        return LogLevel.warn
      case 'info':
        return LogLevel.info
      case 'verbose':
        return LogLevel.verbose
      default:
        return LogLevel.info
    }
  }
  function getLevel () {
    return this.level
  }

  function defaultPrintFunction (levelTag, timestamp) {
    return levelTag + ' ' + timestamp + ' | '
  }
  /**
  * 默认的时间格式化函数
  * @param date 时间
  * @return {string}
  */
  function defaultDateFormatFunction (date) {
    var hour = date.getHours()
    var min = date.getMinutes()
    var sec = date.getSeconds()
    var stampStr = ''
    stampStr += (hour < 10) ? ('0' + hour) : hour
    stampStr += ':'
    stampStr += (min < 10) ? ('0' + min) : min
    stampStr += ':'
    stampStr += (sec < 10) ? ('0' + sec) : sec
    return stampStr
  }

  /**
    * 打印error日志，支持格式化字符：%s, %d, %j
    * @param message
    * @param args
    */
  function error (message, args) {
    if (this.isLevelEnabled(LogLevel.error)) {
      var len = arguments.length
      var funcArgs = []
      for (var sum = 0; sum < len; sum += 1) {
        funcArgs.push(arguments[sum])
      }
      funcArgs.unshift(LogLevel.error)
      this.log.apply(this, funcArgs)
    }
  }

  function isVerboseEnabled () {
    return this.isLevelEnabled(LogLevel.verbose)
  }
  function isLevelEnabled (level) {
    return this.level >= level
  }
  function log () {
    //var timestamp = this.dateFormatFunction(new Date())
    var len = arguments.length
    // const args = Array.prototype.slice.call(arguments, 3) || []
    var logLevel = arguments[0]
    //var msg = this.printFunction(this.getLevelTag(logLevel), timestamp)
    var funcArgs = []
    for (var sum = 1; sum < len; sum += 1) {
      funcArgs.push(arguments[sum])
    }

    var res = sprintf.apply(null, funcArgs) || []
    //res.unshift(msg)
    console.log.apply(console, res)
  }
  /**
   * 打印warn日志，支持格式化字符：%s, %d, %j
   * @param message
   * @param args
   */
  function warn () {
    if (this.isLevelEnabled(LogLevel.warn)) {
      var len = arguments.length
      var funcArgs = []
      for (var sum = 0; sum < len; sum += 1) {
        funcArgs.push(arguments[sum])
      }
      funcArgs.unshift(LogLevel.warn)
      this.log.apply(this, funcArgs)
    }
  }
  /**
   * 打印info日志，支持格式化字符：%s, %d, %j
   * @param message
   * @param args
   */
  function info () {
    if (this.isLevelEnabled(LogLevel.info)) {
      var len = arguments.length
      var funcArgs = []
      for (var sum = 0; sum < len; sum += 1) {
        funcArgs.push(arguments[sum])
      }
      funcArgs.unshift(LogLevel.info)
      this.log.apply(this, funcArgs)
    }
  }
  /**
   * 打印verbose日志，支持格式化字符：%s, %d, %j
   * @param message
   * @param args
   */
  function verbose () {
    if (this.isLevelEnabled(LogLevel.verbose)) {
      var len = arguments.length
      var funcArgs = []
      for (var sum = 0; sum < len; sum += 1) {
        funcArgs.push(arguments[sum])
      }
      funcArgs.unshift(LogLevel.verbose)
      this.log.apply(this, funcArgs)
    }
  }
  this.logLevelName = logLevelName.bind(this)
  this.level = this.logLevelName(this.levelName)
  this.printFunction = defaultPrintFunction.bind(this)
  this.dateFormatFunction = defaultDateFormatFunction.bind(this)
  this.getLevelTag = getLevelTag.bind(this)
  this.getLevel = getLevel.bind(this)
  this.isLevelEnabled = isLevelEnabled.bind(this)
  this.isVerboseEnabled = isVerboseEnabled.bind(this)
  this.log = log.bind(this)
  this.error = error.bind(this)
  this.warn = warn.bind(this)
  this.verbose = verbose.bind(this)
  this.info = info.bind(this)
}
