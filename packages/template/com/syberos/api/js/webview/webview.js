/* eslint-disable no-unused-vars */
/* eslint-disable no-undef */
// 正常加载
var WebviewStatusShow = 0
// 被pop打开
var WebviewStatusPop = 1

function WebView (options) {
  // 默认参数
  var defaultOpts = {
    id: 'webview',
    name: 'webview',
    module: 'webview',
    source: '../qml/swebview.qml',
    methods: ['reload', 'goBack', 'redirectTo', 'navigateTo'],
    autoCreate: true
  }
  if (options) {
    Object.assign(defaultOpts, options)
  }

  SyberPlugin.call(this, defaultOpts)

  this.currentUrl = null
  this.key = 0

  this.loadSuccess = 0
  var that = this

  this.on('ready', function (webview) {
    logger.verbose('webview:[%s] ,on  ready() start', that.id, pageStack.depth)
    logger.verbose('pageStack depth', pageStack.depth)
    SYBEROS.body = webview
    swebviewCache[that.id] = webview
    swebviews.push(that)
    currentWebview = { id: that.id, webview: webview }
    if (that.currentUrl) {
      logger.verbose('currentUrl:', that.currentUrl)
      webview.url = that.currentUrl
      that.trigger('reload', webview)
    }
    // 成功回调绑定函数
    NativeSdkManager.success.connect(that.onSuccess.bind(that))
    // 错误回调绑定函数
    NativeSdkManager.failed.connect(that.onFailed.bind(that))
    // 绑定订阅函数
    NativeSdkManager.subscribe.connect(that.onSubscribe.bind(that))

    // 绑定消息接受信号
    webview.receiveMessage.connect(function (message) {
      that.onMessageReceived(message, that.id)
    })
    // 绑定keys监听事件
    webview.keyOnReleased.connect(function (event) {
      logger.verbose(' webview.keyOnReleased:[%s]', that.id)
      that.trigger('keyRelease', webview, event)
    })

    NativeSdkManager.request('DevTools*', 12378, '', '')
    NativeSdkManager.request('Package*', 151010, '', '')
  })

  // 页面被打开
  this.on('show', function (status) {
    logger.verbose('Webivew:[%s] , on show() ,status:[%d]', that.id, status)
    // 页面被pop唤起,注销上一级页面
    if (status === WebviewStatusPop) {
      logger.verbose('Webivew:[%s] ,当前打开方式为pop，开始注销上一层', that.id, status)
      var idx = getUpperWebview()
      var dwebview = swebviews[idx]
      // 注销上一层
      if (dwebview) {
        logger.verbose('Webivew:[%s] , 开始destroy', dwebview.id)
        SYBEROS.destroy(dwebview.id)
        swebviews.splice(idx, 1)
        logger.verbose('Webivew:[%s] , destroy完成 ,当前数量: %d', dwebview.id, swebviews.length)
      }
    }
  })

  this.on('hide', function () {

  })

  /**
   * 监听手机key
   */
  this.on('keyRelease', function (webview, event) {
    logger.verbose('webview:[%s] , on  keyRelease() ', that.id, event.key)
    logger.verbose('currentWebview: [%s] ', currentWebview.id)
    // 处理返回键事件
    if (KEYCODE_BACK === event.key) {
      logger.verbose('返回事件 | webview:[%s] | 是否能回退:[%s]:', that.id, webview.canGoBack)
      if (currentWebview.id === that.id && webview.canGoBack) {
        event.accepted = true
        webview.goBack()
      } else {
        event.accepted = true
        // 如果当前有多个weview,则减少栈数
        logger.verbose('webviewdepth : [ %d ]', webviewdepth)
        if (webviewdepth > 0) {
          var idx = getLowerWebview()
          var dwebview = swebviews[idx]
          pageStack.pop()
          webviewdepth -= 1
          currentWebview = { id: dwebview.id, webview: dwebview.object }
          dwebview.trigger('show', WebviewStatusPop)
          // 阻止事件
          return
        }
        logger.verbose('webview:[%s] 不能回退:[%s]', that.id, webview.canGoBack)
      }
    }
  })

  // 接受qml成功返回
  this.on('success', function () {
    logger.verbose('webview:[%s], on success()', that.id)
    var len = arguments.length
    var funcArgs = []
    for (var sum = 0; sum < len; sum += 1) {
      funcArgs.push(arguments[sum])
    }
    logger.verbose('webview on success() funcArgs:', JSON.stringify(funcArgs))

    that.onSuccess.apply(this, funcArgs)
  })
  // 接受qml组件fail返回
  this.on('failed', function () {
    logger.verbose('webview on failed()')
    var len = arguments.length
    var funcArgs = []

    for (var sum = 0; sum < len; sum += 1) {
      funcArgs.push(arguments[sum])
    }
    that.onFailed.apply(this, funcArgs)
  })

  /**
   * request 请求
   * @object qml实例化对象
   * @handlerId 请求ID
   * @param 请求参数
   * @method 请求方法名称
   */
  this.on('reload', function (object, handlerId) {
    logger.verbose('webview:[%s]  ,on reload()', that.id)
    object.reload()
    // 绑定进度事件
    object.reloadSuccess.connect(function (loadProgress) {
      if (loadProgress === 100) {
        if (handlerId) {
          that.trigger('success', handlerId, true)
        }
      }
    })
  })
  // 回退
  this.on('goBack', function (object, handlerId) {
    logger.verbose('webview:[%s] on goBack()', that.id)
    if (object.canGoBack) {
      logger.verbose('object.canGoBack', object.canGoBack)
      object.goBack()
      that.trigger('success', handlerId, true)
    } else {
      that.trigger('failed', handlerId, 1013, false)
    }
  })

  // 关闭所有页面，打开某个页面
  this.on('reLaunch', function (object, handlerId, param) {

  })
  // 保留当前页面，跳转到某个页面
  this.on('navigateTo', function (object, handlerId, param) {
    logger.verbose('webview:[%s] on navigateTo', that.id, JSON.stringify(param))
    logger.verbose('navigateTo swebviews:[%d]', swebviews.length)
    logger.verbose('webviewdepth:[%d]', webviewdepth)
    var dwevview = null
    // 假如在最顶层,则使用底层
    if (webviewdepth + 1 > webviewMaxDepth) {
      var idx = getUpperWebview()
      logger.verbose('当前为最多栈数,使用历史栈:[%d]', idx)
      dwevview = swebviews[idx]
      webviewdepth += 1
      SYBEROS.request(dwevview.module, handlerId, 'redirectTo', param)
    } else {
      var wpId = 'webview_' + (swebviews.length + 1)
      logger.verbose('开始创建新的webview:[%s]', wpId)
      dwevview = new WebView({
        id: wpId,
        module: wpId,
        autoCreate: true,
        page: true
      })
      dwevview.currentUrl = getUrl(param.url)
      // 设定webview的深度为2
      webviewdepth += 1
      SYBEROS.addPlugin(dwevview)
    }
  })

  // 关闭当前页面，跳转到某个页面
  this.on('redirectTo', function (object, handlerId, param) {
    try {
      logger.verbose('webview:[%s] on redirectTo', that.id, JSON.stringify(param))
      var url = getUrl(param.url)
      object.url = url
      // 是否第一次绑定接受信号
      that.firstConnect = false
      // 只做一次信号绑定,防止多次信号被触发
      if (!that.firstConnect) {
        // 设置绑定信号
        that.firstConnect = true
        object.reloadSuccess.connect(function (loadProgress) {
          if (that.loadSuccess === 0 && loadProgress === 100) {
            that.loadSuccess = 1
          } else if (that.loadSuccess === 1) {
            logger.verbose('on redirectTo() reloadSuccess: ', loadProgress)
            if (handlerId) {
              that.trigger('success', handlerId, true)
            } else {
              if (param.type) {
                logger.verbose('开始执行 subscribeEvaluate ', param.type)
                that.subscribeEvaluate(param.handlerName, param.data)
              }
            }
            that.loadSuccess = 0
          }
        })
      }
    } catch (error) {
      logger.error('redirectTo error', error.message)
      that.trigger('failed', handlerId, 0, error.message)
    }
  })
}

WebView.prototype = SyberPlugin.prototype

WebView.prototype.onMessageReceived = function (message, webviewId) {
  logger.verbose('webview:[%s] ,onMessageReceived(): ', webviewId, JSON.stringify(message))

  var model = JSON.parse(message.data)
  var handlerId = model.callbackId
  var method = model.handlerName
  var module = model.module

  // 如果有callbackId 则保存回调信息
  if (handlerId) {
    // 是否为长期回调
    var isLong = model['isLong'] || false
    // 保存到短期中
    responseCallbacks[handlerId] = webviewId
    if (isLong) {
      // 如果需要长期,则保存长期池
      responseCallbacksLongTerm[handlerId] = webviewId
    }
  }
  var funcArgs = {}
  if (model.data) {
    funcArgs = model.data
  }

  logger.verbose('onMessageReceived() content:', handlerId, method, funcArgs)
  // 如果为ui模块
  if (SYBEROS.getPlugin(module, method)) {
    // 请求qml动态模块
    SYBEROS.request(module, handlerId, method, model.data)
    return
  }

  // 因为C++类都为大写开头,所以第一个字母转为大写
  var moduleName = module.charAt(0).toUpperCase() + module.slice(1) + '*'
  NativeSdkManager.request(moduleName, handlerId, method, funcArgs)
}

WebView.prototype.onSuccess = function (handlerId, result) {
  logger.verbose('webview:[%s] ,onSuccess() start', this.id, handlerId)
  if (!handlerId) {
    return
  }

  var webview = currentWebview.webview

  if (!webview) {
    logger.error('Webview onSuccess() webview %s 未找到', webviewId)
    return
  }
  // 返回内容
  var resObj = {
    // handlerName:"handleError",
    responseId: Number(handlerId),
    responseData: {
      result: result
    }
  }
  logger.verbose('Webview onSuccess() return', handlerId, JSON.stringify(resObj))
  webview.experimental.evaluateJavaScript(
    'JSBridge._handleMessageFromNative(' + JSON.stringify(resObj) + ')'
  )
}

WebView.prototype.onSubscribe = function (handlerName, result) {
  logger.verbose('Webview:%s onSubscribe() start', this.id, handlerName, JSON.stringify(result))
  if (handlerName === 'DevToolsReload') {
    this.trigger('reload', this.object)
    return
  }
  if (handlerName === 'onShow') {
    var params = {}
    params.url = result.path
    params.handlerName = handlerName
    params.type = 'onShow'
    params.data = result
    this.trigger('redirectTo', this.object, null, params)
    return
  }
  var resObj = {
    handlerName: handlerName,
    data: {
      result: result
    }
  }
  logger.verbose('onSubscribe() res:', JSON.stringify(resObj))
  var webview = currentWebview.webview
  webview.experimental.evaluateJavaScript(
    'JSBridge._handleMessageFromNative(' + JSON.stringify(resObj) + ')'
  )
}

WebView.prototype.subscribeEvaluate = function (handlerName, data) {
  logger.verbose('Webview:%s subscribeEvaluate () start', this.id)
  var resObj = {
    handlerName: handlerName,
    data: data
  }
  logger.verbose('subscribeEvaluate() res:', JSON.stringify(resObj))
  var webview = currentWebview
  webview.experimental.evaluateJavaScript(
    'JSBridge._handleMessageFromNative(' + JSON.stringify(resObj) + ')'
  )
}

WebView.prototype.onFailed = function (handlerId, errorCode, errorMsg) {
  logger.verbose('Webview:%s , onFailed() start', this.id, handlerId, errorCode, errorMsg)
  var webviewId = this.getWebViewIdByHandlerId(handlerId)
  var webview = currentWebview.webview

  var obj = {
    responseId: Number(handlerId),
    responseData: {
      code: Number(errorCode),
      msg: errorMsg
    }
  }
  logger.verbose('onFailed() res: ', JSON.stringify(obj))
  webview.experimental.evaluateJavaScript(
    'JSBridge._handleMessageFromNative(' + JSON.stringify(obj) + ')'
  )
}

WebView.prototype.getWebViewIdByHandlerId = function (handlerId) {
  logger.verbose('webview:[%s] , getWebViewIdByHandlerId()', this.id, handlerId)
  var webviewId = responseCallbacks[handlerId]
  // 默认先短期再长期
  webviewId = webviewId || responseCallbacksLongTerm[handlerId]
  logger.verbose('webviewId:', webviewId)
  if (!webviewId) {
    logger.error('getWebViewIdByHandlerId() webview未找到', webviewId)
    return
  }
  deleteresponseCallbacks[handlerId]
  return webviewId
}

// 获取默认webview
WebView.prototype.getDefault = function () {
  return swebviewCache[0]
}

// 获取所有webview

WebView.prototype.getAll = function () {
  return swebviewCache
}

WebView.prototype.getWebView = function (id) {
  return swebviewCache[id]
}

/**
 * 获取默认html页面地址
 * @return {String}
 */
function getIndexPath () {
  var url = 'file://' + helper.getWebRootPath() + '/index.html'
  logger.verbose('getIndexPath()', url)
  return url
}
/**
 * url地址转换
 * @param {string} url
 */
function getUrl (url) {
  logger.verbose('getUrl() url', url)
  if (!url) {
    throw new Error('url不存在', url)
  }
  // 如果是网络地址,直接返回
  if (url.startsWith('http') || url.startsWith('https')) {
    logger.verbose('http||https  url:', url)
    return url
  }

  var filePath = helper.getWebRootPath() + '/' + url
  var checkPath
  logger.verbose('filePath:', filePath)
  if (filePath.indexOf('?') >= 0) {
    checkPath = filePath.split('?')[0]
  } else {
    checkPath = filePath
  }
  if (helper.exists(checkPath)) {
    var rurl = 'file://' + filePath
    return rurl
  } else {
    logger.verbose('页面不存在:', checkPath, '跳转到index.html')
    return 'file://' + helper.getWebRootPath() + '/index.html'
  }
}
/**
 * 获取上一层webview的索层
 * return {number} 上一层的索引层
 */
function getUpperWebview () {
  var idx
  // 如果最顶层,则使用第二层,因为第一层是最初界面
  if (webviewdepth + 1 > webviewMaxDepth) {
    idx = 1
  } else {
    idx = webviewdepth + 1
  }
  logger.verbose('getUpperWebview() : [ %d ]', idx)
  return idx
}
/**
 * 获取下一层webview的索层
 * return {number} 小一层的索引层
 */
function getLowerWebview () {
  var idx
  if (webviewdepth === 0) {
    idx = 0
  } else {
    idx = webviewdepth - 1
  }
  logger.verbose('getLowerWebview() : [ %d ]', idx)
  return idx
}
