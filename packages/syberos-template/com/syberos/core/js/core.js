/**
 * Syber core Function
 */
function Syber () {
  this.version = '1.0.0'
  this.isInited = false
  this.pluginList = {}
  // 根节点
  this.root = null
  this.option = {
    defaultPlugins: ['root', 'webview']
  }

  this.init()
}

Syber.prototype.init = function () {
  if (this.isInited) {
    console.warn('Syber 已被初始化,不可重复初始化')
  }
  this.isInited = true
}

Syber.prototype.addPlugin = function (plugin) {
  // ignore this plugin if it has already been installed
  if (this.pluginList[plugin.id] !== undefined) {
    console.debug('Plugin ' + plugin.id + ' has already been added.')
    return false
  }
  this.pluginList[plugin.id] = plugin
  // init plugin only if vConsole is ready
  if (this.isInited) {
    this._initPlugin(plugin)
  }
  return true
}

/**
 * init a plugin
 * @private
 */
Syber.prototype._initPlugin = function (plugin) {
  var that = this
  // start init
  plugin.trigger('init')
  // end init
  plugin.isReady = true
  plugin.trigger('ready')
}
