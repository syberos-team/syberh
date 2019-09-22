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

function isArray (value) {
  return Object.prototype.toString.call(value) === '[object Array]'
}

function isFunction (value) {
  return Object.prototype.toString.call(value) === '[object Function]'
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
