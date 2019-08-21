/* eslint-disable no-unused-vars */
/* eslint-disable no-undef */

var sybero = null

function WebView (options) {
  // 默认参数
  var defaultOpts = {
    id: 'webview',
    name: 'webview',
    module: 'webview',
    source: '../qml/swebview.qml',
    methods: ['reload', 'goBack', 'redirectTo'],
    autoCreate: true
  }
  if (options) {
    Object.assign(defaultOpts, options)
  }

  SyberPlugin.call(this, defaultOpts)

  // 定义数组,保存所有webivew
  this._webviews = {}

  this.key = 0
  // 在原生调用完对应的方法后,会执行对应的回调函数id，并删除
  this.responseCallbacks = {}
  // 长期存在的回调，调用后不会删除
  this.responseCallbacksLongTerm = {}

  var that = this

  this.on('ready', function (webview) {
    // var webview = data.object
    SYBEROS.body = webview
    that._webviews[that.id] = webview
    // sybero = sb
    console.log('visible', webview.visible)
    // 成功回调绑定函数
    NativeSdkManager.success.connect(that.onSuccess.bind(that))
    // 错误回调绑定函数
    NativeSdkManager.failed.connect(that.onFailed.bind(that))
    // 绑定消息接受信号
    webview.receiveMessage.connect(function (message) {
      that.onMessageReceived(message, that.id)
    })
    // 绑定keys监听事件
    webview.keyOnReleased.connect(function (event) {
      that.trigger('keyRelease', webview, event)
    })
  })

  /**
   * 监听手机key
   */
  this.on('keyRelease', function (webview, event) {
    console.log('\n----------------event.key', typeof event.key)
    // 处理返回键事件
    if (KEYCODE_BACK === event.key) {
      if (webview.canGoBack) {
        event.accepted = true
        webview.goBack()
      } else {

      }
    }
  })

  // 接受qml成功返回
  this.on('success', function () {
    var len = arguments.length
    var funcArgs = []

    for (var sum = 0; sum < len; sum += 1) {
      funcArgs.push(arguments[sum])
    }
    console.log('--------\n   funcArgs  \n', JSON.stringify(funcArgs))

    that.onSuccess.apply(this, funcArgs)
  })
  // 接受qml组件fail返回
  this.on('failed', function () {
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
    object.reload()
    // 绑定进度事件
    object.reloadSuccess.connect(function (loadProgress) {
      if (loadProgress === 100) {
        that.trigger('success', handlerId, true)
      }
    })
  })
  // 回退
  this.on('goBack', function (object, handlerId) {
    if (object.canGoBack) {
      object.goBack()
      that.trigger('success', handlerId, true)
    } else {
      that.trigger('failed', handlerId, 0, false)
    }
  })

  // 转向某个url
  this.on('redirectTo', function (object, handlerId, param) {
    try {
      var url = getUrl(param.url)
      object.url = url
      that.trigger('success', handlerId, true)
    } catch (error) {
      console.error(error.message)
      that.trigger('failed', handlerId, 0, error.message)
    }
  })
}

WebView.prototype = SyberPlugin.prototype

WebView.prototype.onMessageReceived = function (message, webviewId) {
  console.log(
    '@@@ ',
    'WebView received Message: ',
    typeof message,
    webviewId,
    JSON.stringify(message),
    '\r\n'
  )

  var model = JSON.parse(message.data)
  var handlerId = model.callbackId
  var method = model.handlerName
  var module = model.module

  // print('\n  typeof handlerId', handlerId, typeof handlerId)
  // 如果有callbackId 则保存回调信息
  if (handlerId) {
    // 是否为长期回调
    var isLong = model['isLong'] || false
    // 保存到短期中
    this.responseCallbacks[handlerId] = webviewId
    if (isLong) {
      // 如果需要长期,则保存长期池
      this.responseCallbacksLongTerm[handlerId] = webviewId
    }
  }
  var funcArgs = {}
  if (model.data) {
    funcArgs = model.data
  }

  console.log('\n -------------------', handlerId, method, funcArgs)
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
  console.log('----handlerId \n', handlerId)
  if (!handlerId) {
    return
  }
  var webviewId = this.getWebViewIdByHandlerId(handlerId)
  var webview = this.getWebView(webviewId)

  if (!webview) {
    console.error('webview未找到')
    return
  }
  print('request sucess ', result)
  print('responseID ', handlerId)
  // gToast.requestToast('request sucess：' + JSON.stringify(result))
  // 返回内容
  var resObj = {
    responseId: Number(handlerId),
    responseData: {
      result: result
    }
  }
  webview.experimental.evaluateJavaScript(
    'JSBridge._handleMessageFromNative(' + JSON.stringify(resObj) + ')'
  )
}

WebView.prototype.onFailed = function (handlerId, errorCode, errorMsg) {
  print('\n request handlerId', typeof handlerId)
  var webviewId = this.getWebViewIdByHandlerId(handlerId)
  var webview = this.getWebView(webviewId)

  var obj = {
    responseId: Number(handlerId),
    responseData: {
      code: 0,
      msg: errorMsg
    }
  }
  print('\n request failed ', JSON.stringify(obj))
  webview.experimental.evaluateJavaScript(
    'JSBridge._handleMessageFromNative(' + JSON.stringify(obj) + ')'
  )
}

WebView.prototype.getWebViewIdByHandlerId = function (handlerId) {
  print(
    '\n ------getWebViewIdByHandlerId()-----',
    handlerId,
    JSON.stringify(this.responseCallbacks)
  )
  var webviewId = this.responseCallbacks[handlerId]

  // 默认先短期再长期
  webviewId = webviewId || this.responseCallbacksLongTerm[handlerId]
  print('\n ------getWebViewIdByHandlerId()-----', webviewId)
  if (!webviewId) {
    console.error('webview未找到')
    return
  }
  delete this.responseCallbacks[handlerId]
  return webviewId
}

// 获取默认webview

WebView.prototype.getDefault = function () {
  return this._webviews[0]
}

// 获取所有webview

WebView.prototype.getAll = function () {
  return this._webviews
}

WebView.prototype.getWebView = function (id) {
  return this._webviews[id]
}

/**
 * 获取默认html页面地址
 * @return {String}
 */
function getIndexPath () {
  var url = 'file://' + helper.getWebRootPath() + '/index.html'
  console.debug('\n url', url, '\n')
  return url
}
/**
 * url地址转换
 * @param {string} url
 */
function getUrl (url) {
  if (!url) {
    throw new Error('url不存在', url)
  }
  // 如果是网络地址,直接返回
  if (url.startsWith('http') || url.startsWith('https')) {
    return url
  }

  var filePath = helper.getWebRootPath() + '/' + url
  console.log('--------filePath', filePath)
  if (helper.exists(filePath)) {
    var rurl = 'file://' + filePath
    return rurl
  } else {
    throw new Error('页面不存在')
  }
}
