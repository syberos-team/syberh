/* eslint-disable new-cap */
/* eslint-disable no-undef */
/**
 * Syber core Function
 */

function Syber (parent) {
  this.version = '1.0.0'
  this.isInited = false
  this.pluginList = {}
  this.modules = {}
  // 根节点
  // eslint-disable-next-line node/no-deprecated-api
  this._root = parent || root

  this.body = null

  if (!this._root) {
    throw new Error('root 不存在')
  }
  this.option = {
    defaultPlugins: ['alert', 'confirm', 'camera']
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
 * 根据模块和method获取plugin
 * @module 插件ID
 * @handlerId 请求ID
 * @method 请求方法名称
 * @param 请求参数
 */
Syber.prototype.getPlugin = function (module, method) {
  var rPlugin = null
  for (var key in this.pluginList) {
    var plugin = this.pluginList[key]
    // 如果模块名称匹配,判断方法是否匹配
    if (plugin && plugin.module === module) {
      for (var i = 0; i < plugin.methods.length; i++) {
        if (plugin.methods[i] === method) {
          return plugin
        }
      }
    }
  }

  return rPlugin
}

/**
 * 动态组件请求
 * @module 插件ID
 * @handlerId 请求ID
 * @method 请求方法名称
 * @param 请求参数
 */
Syber.prototype.request = function (module, handlerId, method, param) {
  var plugin = this.getPlugin(module, method)
  // this.pluginList[pluginID]
  if (!plugin) {
    console.error('Plugin ', +module, method, ' 不存在.')
    return false
  }
  // 参数处理
  plugin.setParam(handlerId, param)

  if (plugin.isReady) {
    console.log('plugin isReady', plugin.id)
    // 直接调用
    plugin.trigger(method, plugin.object, handlerId, param)
    return
  }

  // 创建完成后发送request
  this._initPlugin(plugin, null, function (object) {
    plugin.trigger(method, object, handlerId, param)
  })
}

/**
 *@param plugin {Object} 插件
 *@param parent {Object} 挂载节点
 *@param callback {function}
 */
Syber.prototype._initPlugin = function (plugin, parent, callback) {
  // 如果需要单独打开一个页面的话
  if (plugin.page) {
    this.pageStack(plugin, callback)
  } else {
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
        plugin.trigger('ready', incubator.object)

        if (typeof callback === 'function') callback(incubator.object)
      }
    }
  }
}
// pageStack
Syber.prototype.pageStack = function (plugin, callback) {
  var object = pageStack.push(Qt.resolvedUrl(plugin.source), plugin.param)
  plugin.trigger('ready', incubator.object)
  if (callback) callback(object)
  // tackPhoto.imageConfirmed.connect(function (filePath) { // 处理信号
  //   icon.source = 'file://' + filePath
  //   pageStack.pop(main)
  // })
}

/**
 * add built-in plugins
 */
Syber.prototype._addBuiltInPlugins = function () {
  // add default log plugin

  // 建立全局webview
  var vm = new WebView()
  WEBVIEWCORE = vm
  this.addPlugin(vm)

  // add other built-in plugins according to user's config
  var list = this.option.defaultPlugins
  var plugins = {
    alert: { proto: Alert },
    confirm: { proto: Confirm },
    camera: { proto: Camera }
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
