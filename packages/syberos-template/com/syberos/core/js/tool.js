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

function isFunction(value) {
  return Object.prototype.toString.call(value) === '[object Function]';
}
