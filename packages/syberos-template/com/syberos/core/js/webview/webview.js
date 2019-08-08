/* eslint-disable no-unused-vars */
/* eslint-disable no-undef */

var sybero = null

function WebView (options) {
  // 默认参数
  var defaultOpts = {
    id: 'webview',
    name: 'webview',
    source: '../qml/swebview.qml',
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
    NativeSdkManager.sucess.connect(that.onSuccess.bind(that))
    // 错误回调绑定函数
    NativeSdkManager.failed.connect(that.onFailed.bind(that))

    webview.receiveMessage.connect(function (message) {
      that.onMessageReceived(message, that.id)
    })
    console.log('--------\n   webview  \n')
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
    //    var keys = Object.keys(model.data)
    //    // 关联callbackId和webview

    //    for (var i in keys) {
    //      print('@@@ ', 'key: ', i, keys[i], '\r\n')
    //      print('@@@ value is', model.data[keys[i]])
    //      funcArgs[keys[i]] = model.data[keys[i]]
    //    }
  }
  // 如果为ui模块
  if (uiModules[module]) {
    // 约定插件IDhandlerName
    var pluginID = model.handlerName
    SYBEROS.create(pluginID, model.data)
    return
  }

  console.log('\n -------------------', handlerId, method, funcArgs)
  NativeSdkManager.request('TestHandler*', handlerId, method, funcArgs)
}

WebView.prototype.onSuccess = function (handlerId, result) {
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
  gToast.requestToast('request sucess ' + result)
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
