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
    defaultPlugins: ['alert', 'confirm']
  }

  // add 内置 plugins
  this._addBuiltInPlugins()

  this._render()
}
/**
 * render panel
 * @private
 */
Syber.prototype._render = function () {
  var that = this
  // 初始化插件
  this._initPlugin(RootItem, this._root)
  RootItem.on('ready', function (obj) {
    // 设置跟节点
    that.body = obj
    console.log('\n ----RootItem-on ready \n')
    that._autoRun()
  })
}

/**
 * 创建组件
 * @pluginID 插件ID
 * @param 参数
 */
Syber.prototype.create = function (pluginID, param) {
  var plugin = this.pluginList[pluginID]
  if (!plugin) {
    console.error('Plugin ' + pluginID + ' 不存在.')
    return false
  }
  // 参数处理
  plugin.extendParam(param)

  if (plugin.isReady) {
    console.log('plugin isReady', plugin.id)
    // 直接调用
    plugin.onReady()
    return
  }
  this._initPlugin(plugin)
}

/**
 *@param plugin {Object} 插件
 *@param parent {Object} 挂载节点
 */
Syber.prototype._initPlugin = function (plugin, parent) {
  var that = this
  var _parent = parent || this.body
  console.debug('\n ***********plugin', JSON.stringify(plugin), '\n')
  console.debug('\n ***********plugin.source', plugin.source, '\n')
  console.debug('\n ***********_parent', _parent, '\n')
  var component = Qt.createComponent(plugin.source)

  if (component.status === Component.Error) {
    console.error('\n initPlugin Error', component.status)
    return
  }
  var incubator = component.incubateObject(_parent)
  incubator.onStatusChanged = function (status) {
    if (status === Component.Ready) {
      plugin.object = incubator.object
      plugin.isReady = true
      // data数据
      var data = { object: incubator.object }
      plugin.trigger('ready', incubator.object)
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
    alert: { proto: Alert },
    confirm: { proto: Confirm }
  }
  if (!!list && isArray(list)) {
    for (var i = 0; i < list.length; i++) {
      var tab = plugins[list[i]]
      if (tab) {
        this.addPlugin(new tab.proto())
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
    var plugin = this.pluginList[id]
    if (plugin.autoCreate) {
      this._initPlugin(plugin)
    }
  }
  this.triggerEvent('ready')
}

Syber.prototype.addPlugin = function (plugin) {
  console.log('\n addPlugin \n', typeof plugin, '\n')
  // console.log('\n addPlugin \n', JSON.stringify(plugin), '\n')
  // ignore this plugin if it has already been installed
  if (this.pluginList[plugin.id] !== undefined) {
    console.debug('Plugin ' + plugin.id + ' has already been added.')
    return false
  }
  this.pluginList[plugin.id] = plugin

  // init plugin only if Syber is ready
  if (this.isInited && plugin.autoCreate) {
    this._initPlugin(plugin)
  }
  return true
}
/**
 * remove a plugin
 * @public
 * @param string pluginID
 * @return boolean
 */
Syber.prototype.removePlugin = function (pluginID) {
  pluginID = (pluginID + '').toLowerCase()
  var plugin = this.pluginList[pluginID]
  // skip if is has not been installed
  if (plugin === undefined) {
    console.debug('Plugin ' + pluginID + ' does not exist.')
    return false
  }

  plugin.trigger('remove')

  try {
    delete this.pluginList[pluginID]
  } catch (e) {
    this.pluginList[pluginID] = undefined
  }

  return true
}

/**
 * trigger a Syber.option event
 * @protect
 */
Syber.prototype.triggerEvent = function (eventName, param) {
  eventName = 'on' + eventName.charAt(0).toUpperCase() + eventName.slice(1)
  if (isFunction(this.option[eventName])) {
    this.option[eventName].apply(this, param)
  }
}
