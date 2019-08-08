/* eslint-disable one-var */
/* eslint-disable no-unused-vars */
/**
 * 增加ES6的拓展支持
 */
function polyfill () {
  assignPolyfill()
  keysPolyfill()
}

/**
 * 增加Es6 Object.assign的拓展支持
 */
function assignPolyfill () {
  if (!Object.assign) {
    Object.defineProperty(Object, 'assign', {
      enumerable: false,
      configurable: true,
      writable: true,
      value: function (target, firstSource) {
        if (target === undefined || target === null) {
          throw new TypeError('Cannot convert first argument to object')
        }
        var to = Object(target)
        for (var i = 1; i < arguments.length; i++) {
          var nextSource = arguments[i]
          if (nextSource === undefined || nextSource === null) continue
          var keysArray = Object.keys(Object(nextSource))
          for (
            var nextIndex = 0, len = keysArray.length;
            nextIndex < len;
            nextIndex++
          ) {
            var nextKey = keysArray[nextIndex]
            var desc = Object.getOwnPropertyDescriptor(nextSource, nextKey)
            if (desc !== undefined && desc.enumerable) {
              to[nextKey] = nextSource[nextKey]
            }
          }
        }
        return to
      }
    })
  }
}

/**
 * 旧环境中添加兼容的Object.keys
 */
function keysPolyfill () {
  if (!Object.keys) {
    Object.keys = (function () {
      var hasOwnProperty = Object.prototype.hasOwnProperty,
        hasDontEnumBug = !{ toString: null }.propertyIsEnumerable('toString'),
        dontEnums = [
          'toString',
          'toLocaleString',
          'valueOf',
          'hasOwnProperty',
          'isPrototypeOf',
          'propertyIsEnumerable',
          'constructor'
        ],
        dontEnumsLength = dontEnums.length

      return function (obj) {
        if (
          (typeof obj !== 'object' && typeof obj !== 'function') ||
          obj === null
        ) {
          throw new TypeError('Object.keys called on non-object')
        }

        var result = []

        for (var prop in obj) {
          if (hasOwnProperty.call(obj, prop)) result.push(prop)
        }

        if (hasDontEnumBug) {
          for (var i = 0; i < dontEnumsLength; i++) {
            if (hasOwnProperty.call(obj, dontEnums[i])) {
              result.push(dontEnums[i])
            }
          }
        }
        return result
      }
    })()
  }
}

function valuesPolyfill () {
  if (!Object.values) {
    Object.values = function (obj) {
      if (obj !== Object(obj)) {
        throw new TypeError('Object.values called on a non-object')
      }
      var val = [],
        key
      for (key in obj) {
        if (Object.prototype.hasOwnProperty.call(obj, key)) {
          val.push(obj[key])
        }
      }
      return val
    }
  }
}
