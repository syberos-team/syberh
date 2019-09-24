/* eslint-disable no-unused-vars */
/**
 * 生成UUID
 */
function getSizeStr (bytes) {
  var unit = ['B', 'KB', 'MB', 'GB', 'TB']
  var i = 0
  if (bytes < 0) {
    print('bytes wrong: ', bytes)
    return '0'
  }

  while (bytes > 1024 && i < unit.length) {
    bytes /= 1024.0
    i++
    // str = Number(bytes).toPrecision(4) + unit[i]
  }

  var precision = bytes >= 1000 ? 4 : 3
  return Number(bytes).toPrecision(precision) + unit[i]
}

function getDir (filePath) {
  if (filePath === '') { return '' } else { return filePath.substr(0, filePath.lastIndexOf('/')) }
}

var selectArr = [1, 2]

function setArr (arr) {
  selectArr = arr
}

function getArr (arr) {
  return selectArr
}

function uuid (_length) {
  var leg = _length || 5

  return Number(
    Math.random()
      .toString()
      .substr(3, leg) + Date.now()
  ).toString(36)
}

/**
 * 是否同一个url
 * @param {string} url 
 * @param {string} diffUrl
 * @returns {boolean}  
 */
function diffUrl (url, diffUrl) {
  logger.verbose('tool diffUrl() url:%s', url, typeof url)
  logger.verbose('tool diffUrl() diffUrl:', diffUrl)

  if (!url || !diffUrl) {
    logger.verbose('tool diffUrl() url or diffUrl is undefined')
    return false;
  }
  var checkPath
  if (diffUrl.indexOf('?') >= 0) {
    checkPath = diffUrl.split('?')[0]
  } else {
    checkPath = diffUrl
  }

  logger.verbose('tool diffUrl() checkPath: %s', checkPath)
  var ret = url.indexOf(checkPath) === -1 ? false : true;
  logger.verbose('tool diffUrl() ret: %s', ret)
  return ret
}

/**
 * determines whether the passed value is a specific type
 * @param mixed value
 * @return boolean
 */
function isNumber (value) {
  return Object.prototype.toString.call(value) == '[object Number]';
}
function isString (value) {
  return Object.prototype.toString.call(value) == '[object String]';
}
function isArray (value) {
  return Object.prototype.toString.call(value) === '[object Array]'
}

function isFunction (value) {
  return Object.prototype.toString.call(value) === '[object Function]'
}
function isBoolean (value) {
  return Object.prototype.toString.call(value) == '[object Boolean]';
}
function isUndefined (value) {
  return value === undefined;
}
function isNull (value) {
  return value === null;
}
function isSymbol (value) {
  return Object.prototype.toString.call(value) == '[object Symbol]';
}

function isObject (value) {
  return (
    Object.prototype.toString.call(value) == '[object Object]'
    ||
    // if it isn't a primitive value, then it is a common object
    (
      !isNumber(value) &&
      !isString(value) &&
      !isBoolean(value) &&
      !isArray(value) &&
      !isNull(value) &&
      !isFunction(value) &&
      !isUndefined(value) &&
      !isSymbol(value)
    )
  );
}

function getStrLength (inputStr) {
  var currLength = 0
  if (!inputStr) {
    return currLength
  }

  for (var i = 0; i < inputStr.length; i++) {
    var item = inputStr.charAt(i)
    // 中文字符的长度经编码之后大于4
    if (escape(item).length > 4) {
      currLength += 2
    } else {
      currLength += 1
    }
  }
  return currLength
}
