/* eslint-disable no-undef */
/**
 * Syber core Function
 */

function Syber (parent) {
  this.version = '1.0.0'
  this.isInited = false
  this.pluginList = {}
  // 根节点
  this._root = parent || root

  this.body = null

  if (!this._root) {
    throw new Error('root 不存在')
  }
  this.option = {
    defaultPlugins: []
  }

  // add built-in plugins
  this._addBuiltInPlugins()

  this._render()
}
/**
 * render panel
 * @private
 */
Syber.prototype._render = function () {
  var that = this
  this._create(RootItem)
  RootItem.on('ready', function (obj) {
    // 设置跟节点
    this.body = obj
    that._autoRun()
    console.log('\n ----rootItem-onReady')
  })
}

/**
 *@param plugin {Object}
 *@param parent {Object} 挂载节点
 *@param callback {?function} 回调函数
 */
Syber.prototype._create = function (plugin, parent) {
  var _parent = parent || this._root
  console.log("\n ***********plugin.source",plugin.source,'\n')
  var component = Qt.createComponent(plugin.source)
  var incubator = component.incubateObject(_parent)

  if (incubator.status !== Component.Ready) {
    incubator.onStatusChanged = function (status) {
      if (status === Component.Ready) {
        console.log('\n  Component.Ready', Component.Ready)
        plugin.isReady = true
        plugin.trigger('ready', incubator.object)
      }
    }
  }
}

/**
 * add built-in plugins
 */
Syber.prototype._addBuiltInPlugins = function () {
  // add default log plugin
  this.addPlugin(new WebView())

  // add other built-in plugins according to user's config
  var list = this.option.defaultPlugins
  var plugins = {
    // webview: { proto: WebView, id: 'webview', parent: this.body }
  }
  if (!!list && isArray(list)) {
    for (var i = 0; i < list.length; i++) {
      var tab = plugins[list[i]]
      if (tab) {
        this.addPlugin(new tab.proto(list[i], tab.name))
      } else {
        console.debug('Unrecognized default plugin ID:', list[i])
      }
    }
  }
}

/**
 * auto run after initialization
 * @private
 */
Syber.prototype._autoRun = function () {
  this.isInited = true

  // init plugins
  for (var id in this.pluginList) {
    this._initPlugin(this.pluginList[id])
  }

  this.triggerEvent('ready')
}

Syber.prototype.init = function () {
  if (this.isInited) {
    console.warn('Syber 已被初始化,不可重复初始化')
  }
  console.log('\n Syber 已被初始化')
  this.isInited = true
}

Syber.prototype.addPlugin = function (plugin) {

    console.log('-------\n')
     console.log(JSON.stringify(plugin))
     console.log('-------\n')
     console.log(typeof plugin.trigger)
     console.log('-------\n')

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
  this._create(plugin)
}

/**
  * trigger a vConsole.option event
  * @protect
  */
 Syber.prototype.triggerEvent=function(eventName, param) {
   eventName = 'on' + eventName.charAt(0).toUpperCase() + eventName.slice(1);
   if (isFunction(this.option[eventName])) {
     this.option[eventName].apply(this, param);
   }
 }

