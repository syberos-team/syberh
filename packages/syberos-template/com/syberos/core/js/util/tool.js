/* eslint-disable no-unused-vars */
/**
 * 生成UUID
 */

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
