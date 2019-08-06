/**
 * Syber Plugin Function
 */
function SyberPlugin (id, module, name) {
  this.id = id
  this.module = module
  this.name = name || 'newPlugin'
  this.eventList = {}
}

SyberPlugin.prototype.getId = function () {
  return this.id
}

SyberPlugin.prototype.setId = function (id) {
  this.id = id
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
