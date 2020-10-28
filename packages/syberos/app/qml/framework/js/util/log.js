/* eslint-disable no-unused-vars */
/* eslint-disable no-undef */

/**
 * 日志工具类
 */
function Logger(levelName, printTag) {

  this.LogLevel = {
    error: 1,
    warn: 2,
    info: 3,
    verbose: 4
  };

  this.toLevel = function(levelName) {
    switch (levelName) {
      case 'error':
        return this.LogLevel.error;
      case 'warn':
        return this.LogLevel.warn;
      case 'info':
        return this.LogLevel.info;
      case 'verbose':
        return this.LogLevel.verbose;
      default:
        return this.LogLevel.info;
    }
  }

  this.levelName = levelName ? levelName : 'info';
  this.level = this.toLevel(this.levelName);
  this.isPrintTag = !!printTag
}

Logger.prototype.toLevelTag = function(level) {
  switch (level) {
    case this.LogLevel.error:
      return 'ERR ';
    case this.LogLevel.warn:
      return 'WARN';
    case this.LogLevel.info:
      return 'INFO';
    case this.LogLevel.verbose:
      return 'VERB';
  }
}

Logger.prototype.getLevel = function() {
  return this.level;
}

Logger.prototype.isLevelEnabled = function(level) {
  return this.level >= level;
}

Logger.prototype.isVerboseEnabled = function() {
  return this.isLevelEnabled(this.LogLevel.verbose);
}

Logger.prototype.isInfoEnabled = function() {
  return this.isLevelEnabled(this.LogLevel.info);
}

Logger.prototype.isWarnEnabled = function() {
  return this.isLevelEnabled(this.LogLevel.warn);
}

Logger.prototype.isErrorEnabled = function() {
  return this.isLevelEnabled(this.LogLevel.error);
}

Logger.prototype.error = function() {
    if (!this.isErrorEnabled()) {
      return;
    }
    if(arguments && arguments.length > 0){
      this.log(this.LogLevel.error, Array.apply(null, arguments));
    }
  }

Logger.prototype.warn = function() {
  if (!this.isWarnEnabled()) {
    return;
  }
  if(arguments && arguments.length > 0){
    this.log(this.LogLevel.warn, Array.apply(null, arguments));
  }
}

Logger.prototype.info = function() {
  if (!this.isInfoEnabled()) {
    return;
  }
  if(arguments && arguments.length > 0){
    this.log(this.LogLevel.info, Array.apply(null, arguments));
  }
}

Logger.prototype.verbose = function() {
  if (!this.isVerboseEnabled()) {
    return;
  }
  if(arguments && arguments.length > 0){
    this.log(this.LogLevel.verbose, Array.apply(null, arguments));
  }
}

Logger.prototype.log = function(level, args) {
  if(!args || args.length === 0){
    console.log('');
    return;
  }
  var res = '';
  if(args.length === 1){
    res = args[0];
  }else{
    res = this.sprintf(args);
  }
  if(this.isPrintTag){
    console.log(this.tag(level), res || '');
  }else{
    console.log(res || '');
  }
}

Logger.prototype.sprintf = function(args) {
  var message = args[0];
  var i = 1;
  var sprintfMessage = message.replace(/%((%)|s|d|f|j)/g, function (m) {
    var val = args[i];
    i++;
    if(!val){
      return '';
    }
    switch(m){
      case '%s':
        return val;
      case '%d':
        return val;
      case '%f':
        return val;
      case '%j':
        return JSON.stringify(val);
      default:
        return m;
    }
  });
  if(i < args.length){
    return sprintfMessage + ' ' + args.slice(i).join(' ')
  }
  return sprintfMessage;
}

Logger.prototype.tag = function(level) {
  return this.toLevelTag(level) + ' ' + this.timeFormat() + ' |';
}

Logger.prototype.timeFormat = function(date) {
  if(!date){
    date = new Date();
  }
  var hour = date.getHours();
  var min = date.getMinutes();
  var sec = date.getSeconds();
  var stampStr = '';
  stampStr += hour < 10 ? '0' + hour : hour;
  stampStr += ':';
  stampStr += min < 10 ? '0' + min : min;
  stampStr += ':';
  stampStr += sec < 10 ? '0' + sec : sec;
  return stampStr;
}

var logger = new Logger((typeof helper !== 'undefined') ? helper.logLevelName() : 'info', false);
