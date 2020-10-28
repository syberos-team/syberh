/* eslint-disable no-unused-vars */
/**
 * 生成UUID
 */
function getSizeStr (bytes) {
  var unit = ['B', 'KB', 'MB', 'GB', 'TB'];
  var i = 0;
  if (bytes < 0) {
    print('bytes wrong: ', bytes);
    return '0';
  }

  while (bytes > 1024 && i < unit.length) {
    bytes /= 1024.0;
    i++;
    // str = Number(bytes).toPrecision(4) + unit[i]
  }

  var precision = bytes >= 1000 ? 4 : 3;
  return Number(bytes).toPrecision(precision) + unit[i];
}

function getDir (filePath) {
  if (filePath === '') { return ''; } else { return filePath.substr(0, filePath.lastIndexOf('/')); }
}

var selectArr = [1, 2];

function setArr (arr) {
  selectArr = arr;
}

function getArr (arr) {
  return selectArr;
}

function uuid (_length) {
  var leg = _length || 5;

  return Number(
    Math.random()
      .toString()
      .substr(3, leg) + Date.now()
  ).toString(36);
}

/**
 * 是否同一个url
 * @param {string} url
 * @param {string} diffUrl
 * @returns {boolean}
 */
function diffUrl (url, diffUrl) {
  logger.verbose('tool diffUrl() url:%s  %s', url, typeof url);
  logger.verbose('tool diffUrl() diffUrl: %s', diffUrl);

  if (!url || !diffUrl) {
    logger.verbose('tool diffUrl() url or diffUrl is undefined');
    return false;
  }
  var checkPath;
  if (diffUrl.indexOf('?') >= 0) {
    checkPath = diffUrl.split('?')[0];
  } else {
    checkPath = diffUrl;
  }

  // 去掉前面的小数点
  if (checkPath.split('')[0] === '.') {
    checkPath = checkPath.slice(1);
  }

  logger.verbose('tool diffUrl() checkPath: %s', checkPath);
  var ret = url.indexOf(checkPath) !== -1;
  logger.verbose('tool diffUrl() ret: %s', ret);
  return ret;
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
  return Object.prototype.toString.call(value) === '[object Array]';
}

function isFunction (value) {
  return Object.prototype.toString.call(value) === '[object Function]';
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
    Object.prototype.toString.call(value) == '[object Object]' ||
    // if it isn't a primitive value, then it is a common object

    !isNumber(value) &&
    !isString(value) &&
    !isBoolean(value) &&
    !isArray(value) &&
    !isNull(value) &&
    !isFunction(value) &&
    !isUndefined(value) &&
    !isSymbol(value)

  );
}

/*! 获取字符串长度。 */
function getStrLength (inputStr) {
  var currLength = 0;
  if (!inputStr) {
    return currLength;
  }

  for (var i = 0; i < inputStr.length; i++) {
    var item = inputStr.charAt(i);
    // 中文字符的长度经编码之后大于4
    if (escape(item).length > 4) {
      currLength += 2;
    } else {
      currLength += 1;
    }
  }
  return currLength;
}

/**
 * url地址转换
 * @param {string} url
 */
function getUrl (url) {
  logger.verbose('getUrl() url %s', url);
  if (!url) {
    throw new Error('url不存在', url);
  }
  // 如果是网络地址,直接返回
  if (/^(http|https|ftp|chrome|\/\/)/g.test(url)) {
    logger.verbose('http||https  url: %s', url);
    return url;
  }

  var filePath = helper.getWebRootPath() + '/' + url;
  var checkPath;
  logger.verbose('filePath: %s', filePath);
  if (filePath.indexOf('?') >= 0) {
    checkPath = filePath.split('?')[0];
  } else {
    checkPath = filePath;
  }
  if (helper.exists(checkPath)) {
    var rurl = 'file://' + filePath;
    return rurl;
  } else {
    throw new Error('url不存在', url);
    // logger.verbose('页面不存在:', checkPath, '跳转到index.html')
    // return 'file://' + helper.getWebRootPath() + '/index.html'
  }
}

/*! 获取最终展现字符串。每行14英文字符的长度 */
function getOutputStr (inputStr, maxRowLength) {
  if (!inputStr) {
    return '';
  }

  var currLength = 0;
  var outputStr = '';
  var lineBreak = false;
  for (var i = 0; i < inputStr.length; i++) {
    var item = inputStr.charAt(i);
    // 中文字符的长度经编码之后大于4
    if (escape(item).length > 4) {
      currLength += 2;
    } else {
      currLength += 1;
    }
    outputStr = outputStr.concat(item);
    // 如果未换行且已达到单行字符串最大长度，则给文本换行
    if (!lineBreak && currLength >= maxRowLength) {
      outputStr = outputStr.concat('\n');
      lineBreak = true;
    }
  }

  // 如果只有一行，则将换行符去掉
  if (outputStr.indexOf('\n') == outputStr.length - 1) {
    outputStr = outputStr.replace('\n', '');
  }
  return outputStr;
}


var UI = {
  /* eslint-disable no-unused-vars */
  ratio: 1, // fileUtils.screenRatio()
  /* all */
  DEFAULT_MARGIN_LEFT: 40,
  DEFAULT_MARGIN_RIGHT: 40,

  /* title bar */
  TITLEBAR_HEIGHT: 106,

  /* no text item */
  NO_TEXTITEM_TOPMARGIN: 303,

  /* file list */
  FILE_LIST_HEIGHT: 160,
  FILE_LIST_ROW_SPACING: 30,
  FILE_LIST_COLUMN_SPACING: 10,
  FILE_ICON_WIDTH: 82,
  FILE_ICON_HEIGHT: 82,
  FILE_NAME_SIZE: 32,
  FILE_INFO_SIZE: 26,
  FILE_INFO_COLOR: '#8d8d8d',
  THUMBNAIL_WIDTH: 160,
  THUMBNAIL_HEIGHT: 160,
  LIST_SEPARATOR_COLOR: '#d4d4d4',
  EDIT_SELECTOR_ICON_WIDTH: 50,
  EDIT_SELECTOR_ICON_HEIGHT: 50
}
