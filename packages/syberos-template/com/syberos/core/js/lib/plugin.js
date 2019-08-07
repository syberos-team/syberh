/**
 * Syber Plugin Function
 */
// eslint-disable-next-line no-unused-vars
function SyberPlugin (opts) {

  if(!opts.id||!opts.module||!opts.name||!opts.source){
    throw new Error("缺少参数");
  }
  this.id = opts.id
  this.module = opts.module
  this.name =opts. name
  this.source=opts.source
  this.isReady=false
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
