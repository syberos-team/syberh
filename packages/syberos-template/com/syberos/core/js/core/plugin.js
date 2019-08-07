/**
 * Syber Plugin Function
 */
// eslint-disable-next-line no-unused-vars
function SyberPlugin (opts) {
  // 是否自动创建,默认只加载插件,不做创建
  this.autoCreate = opts.autoCreate || false
  this.id = opts.id
  this.module = opts.module || 'ui'
  this.name = opts.name
  this.source = opts.source
  this.isReady = false
  // Syber
  this.syber = null
  // 挂载的qml
  this.object = null
  // 插件需要的参数
  this.param = {}
  this.eventList = {}
}

/**
 * 拓展参数
 * @param
 */
SyberPlugin.prototype.extendParam = function (param) {
  if (param) {
    Object.assign(this.param, param)
  } else {
    console.error('SyberPlugin extendParam error,param is undefined')
  }
}

/**
 * register an event
 * @public
 * @param string
 * @param function
 */

SyberPlugin.prototype.on = function (eventName, callback) {
  this.eventList[eventName] = callback
  return this
}

/**
 * trigger an event
 * @public
 * @param string
 * @param mixed
 */
SyberPlugin.prototype.trigger = function (eventName, data) {
  if (typeof this.eventList[eventName] === 'function') {
    // registered by `.on()` method
    this.eventList[eventName].call(this, data)
  } else {
    // registered by `.onXxx()` method
    var method = 'on' + eventName.charAt(0).toUpperCase() + eventName.slice(1)
    if (typeof this[method] === 'function') {
      // eslint-disable-next-line no-useless-call
      this[method].call(this, data)
    }
  }
  return this
}
