/**
 * Syber core Function
 */

function Syber (parent) {
  var qtVersion = helper.getQtVersion();

  //系统版本
  this.moduleVersion = '';
  if(qtVersion < 0x050600){
    this.moduleVersion = '2'
  }else if(qtVersion < 0x050c00){
    this.moduleVersion = '4'
  }else{
    this.moduleVersion = '5'
  }


  this.version = '1.0.0';
  this.isInited = false;
  this.pluginList = {};
  this.modules = {};
  // 根节点
  // eslint-disable-next-line node/no-deprecated-api
  this._root = parent;

  this.body = null;

  if (!this._root) {
    logger.error('Syber() root 不存在');
    throw new Error('root 不存在');
  }
  this.option = {
    defaultPlugins: []  }

  // add 内置 plugins
  this._addBuiltInPlugins();

  this._autoRun();
}
/**
 * render panel
 * @private
 */
Syber.prototype._render = function () {
  var that = this;
  // 初始化插件
  this._initPlugin(RootItem, this._root);
  RootItem.on('ready', function (obj) {
    // 设置跟节点
    that.body = obj;
    that._autoRun();
  });
};
/**
 * 根据插件module和method获取plugin
 * @module {string} 插件module
 * @method {string} 请求方法名称
 */
Syber.prototype.getPlugin = function (module, method) {
  var rPlugin = null;
  for (var key in this.pluginList) {
    var plugin = this.pluginList[key];
    // 如果模块名称匹配,判断方法是否匹配
    if (plugin && plugin.module === module) {
      for (var i = 0; i < plugin.methods.length; i++) {
        if (plugin.methods[i] === method) {
          return plugin;
        }
      }
    }
  }

  return rPlugin;
};

/**
 * 动态组件请求
 * @param module {string} 插件module
 * @param handlerId {number} 请求ID
 * @param method {string} 请求方法名称
 * @param param {Object} 请求参数
 */
Syber.prototype.request = function (module, handlerId, method, param) {
  logger.verbose('core request(),module:[%s],method:[%s]', module, method);
  var plugin = this.getPlugin(module, method);
  if (!plugin) {
    console.error('Plugin ', module, method, ' 不存在.');
    return false;
  }
  // 参数处理
  plugin.setParam(handlerId, param);
  if (plugin.isReady) {
    logger.verbose('plugin isReady', plugin.id);
    // 直接调用
    plugin.trigger(method, plugin.object, handlerId, param);
    return;
  }

  // 创建完成后发送request
  this._initPlugin(plugin, null, function (object) {
    plugin.trigger(method, object, handlerId, param);
  });
};

/**
 *@param plugin {Object} 插件
 *@param parent {Object} 挂载节点
 *@param callback {function}
 */
Syber.prototype._initPlugin = function (plugin, parent, callback) {
  logger.verbose('core.js _initPlugin()', plugin.id);
  // 如果需要单独打开一个页面的话
  if (plugin.page) {
    this.pageStack(plugin, callback);
  } else {
    if (!plugin.source) {
      plugin.isReady = true;
      // 对webview进行特殊处理
      if (plugin.id === 'webview') {
        logger.verbose('core.js _initPlugin() _spage:', _spage)
        plugin.object = _spage;
        plugin.trigger('ready', _spage);
      }
      if (typeof callback === 'function') callback();
      return;
    }

    var component = Qt.createComponent(plugin.source);
    if (component.status === Component.Error) {
      logger.error('\n initPlugin Error', component.status);
      return;
    }
    plugin.component = component;

    var _parent = currentWebview.object || _root;
    var incubator = component.incubateObject(_parent);
    if (incubator) {
      plugin.incubator = incubator;
    }
    if (incubator.status !== Component.Ready) {
      incubator.onStatusChanged = function (status) {
        if (status === Component.Ready) {
          plugin.object = incubator.object;
          plugin.isReady = true;
          // 调用事件:ready
          plugin.trigger('ready', incubator.object);
          if (typeof callback === 'function') {
            callback(incubator.object);
          }
        }
      };
    } else {
      print('Object', incubator.object, 'is ready immediately!');
      plugin.object = incubator.object;
      plugin.isReady = true;
      // 调用事件:ready
      plugin.trigger('ready', incubator.object);
      if (typeof callback === 'function') {
        callback(incubator.object);
      }
    }
  }
};

/**
 * 销毁组件
 *@param pluginId {string} 插件ID
 */
Syber.prototype.destroy = function (pluginId) {
  logger.verbose('Syber destroy() pluginId:%s', pluginId);
  if (!pluginId) {
    return;
  }
  var plugin = this.pluginList[pluginId];
  if (!plugin) {
    logger.verbose('Syber destroy() pluginId: [%s] 不存在', pluginId);
    throw new Error('core.js,destroy(),plugin不存在,id:', pluginId);
  }
  if (plugin.page) {
    logger.verbose('Syber destroy() page  pageStack.pop()');
  }

  var component = plugin.component;
  if (component) {
    component.destroy();
    // 释放
    plugin.component = undefined;
    logger.verbose('Syber component.destroy: %s', plugin.id);
  }
  plugin.isReady = undefined;
  plugin.object = undefined;
  plugin.param = {};
  plugin.incubator = undefined;
  plugin.handlerId = undefined;
  logger.verbose('Syber component.destroy: %s', JSON.stringify(plugin));
  if (plugin.removePlugin) {
    logger.info('Syber destroy() plugin.removePlugin : %s', plugin.removePlugin);
    this.removePlugin(pluginId);
    plugin = undefined;
  }
  // pageStack.deleteCachedPage(pluginId)
};

/**
 * 使用pageStack形式打开新的页面
 * @param plugin {Object} 插件
 * @param callback {function} 回调
 */
Syber.prototype.pageStack = function (plugin, callback) {
  logger.verbose('Syber pageStack() start');
  var object = null;
  var cachePage;
  if (plugin.isCache) {
    cachePage = pageStack.getCachedPage(Qt.resolvedUrl(plugin.source),
      plugin.id);
    logger.verbose('Syber pageStack() cachePage', cachePage);
  }
  logger.verbose('Syber pageStack() param: %s ,immediate : %s', JSON.stringify(plugin.param), plugin.immediate);
  if (cachePage) {
    object = pageStack.push(cachePage, plugin.param, plugin.immediate);
  } else {
    object = pageStack.push(Qt.resolvedUrl(plugin.source), plugin.param);
  }
  plugin.object = object;
  plugin.isReady = true;
  plugin.trigger('ready', object);
  if (typeof callback === 'function') {
    callback(object);
  }
  logger.verbose('Syber pageStack() end');
};

/**
 * add built-in plugins
 */
Syber.prototype._addBuiltInPlugins = function () {
  // 建立全局webview
  var webview = new WebView();
  WEBVIEWCORE = webview;
  this.addPlugin(webview);
  var list = this.option.defaultPlugins;
  var plugins = {
  };
  if (!!list && isArray(list)) {
    for (var i = 0; i < list.length; i++) {
      var tab = plugins[list[i]];
      if (tab) {
        this.addPlugin(new tab.proto());
      } else {
        console.debug('Unrecognized default plugin ID:', list[i]);
      }
    }
  }
};

/**
 * auto run after initialization
 * @private
 */
Syber.prototype._autoRun = function () {
  logger.verbose('Syber _autoRun() pluginList:', Object.keys(this.pluginList))
  this.isInited = true;

  // init plugins
  for (var id in this.pluginList) {
    var plugin = this.pluginList[id];
    if (plugin.autoCreate) {
      this._initPlugin(plugin);
    }
  }
  this.triggerEvent('ready');
};

Syber.prototype.addPlugin = function (plugin) {
  logger.verbose('Syber addPlugin() plugin:%s', JSON.stringify(plugin));
  if (this.pluginList[plugin.id] !== undefined) {
    logger.error('Plugin ' + plugin.id + ' has already been added.');
    return false;
  }
  this.pluginList[plugin.id] = plugin;
  // init plugin only if Syber is ready
  logger.verbose('Syber addPlugin() isInited:', this.isInited)
  if (this.isInited && plugin.autoCreate) {
    this._initPlugin(plugin);
  }
  return true;
};
/**
 * remove a plugin
 * @public
 * @param string pluginID
 * @return boolean
 */
Syber.prototype.removePlugin = function (pluginID) {
  pluginID = (pluginID + '').toLowerCase();
  var plugin = this.pluginList[pluginID];
  // skip if is has not been installed
  if (plugin === undefined) {
    console.debug('Plugin ' + pluginID + ' does not exist.');
    return false;
  }

  plugin.trigger('remove');

  try {
    delete this.pluginList[pluginID];
  } catch (e) {
    this.pluginList[pluginID] = undefined;
  }

  return true;
};

/**
 * trigger a Syber.option event
 * @protect
 */
Syber.prototype.triggerEvent = function (eventName, param) {
  eventName = 'on' + eventName.charAt(0).toUpperCase() + eventName.slice(1);
  console.log('core.js triggerEvent eventName:', eventName, ', param:', param, ', func:', this.option[eventName]);
  if (isFunction(this.option[eventName])) {
    this.option[eventName].apply(this, param);
  }
};
