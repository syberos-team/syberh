Qt.include('util.js')

// 构造方法内部封装属性
function WebView (parent) {
  this._parent = parent
  // 定义是否初始化
  this._init = false
  // 默认层级
  this.defalutZ = 10
  // 当前层级
  this.currentZ = this.defalutZ
  // 定义数组,保存所有webivew
  this._webviews = []

  this.key = 0
  // 在原生调用完对应的方法后,会执行对应的回调函数id，并删除
  this.responseCallbacks = {}
  // 长期存在的回调，调用后不会删除
  this.responseCallbacksLongTerm = {}


  if (typeof this.init !== 'function') {
    WebView.prototype.init = function () {
      if (this._init) {
        console.warn('当前已初始化,不可多次初始化')
        return
      }
      var that = this
      this._init = true
      // 调用创建
      this.create(null, function (webview) {
        console.debug('------创建完成', webview.syberObject.key)
        // 注意,要在webview初始化完成后创建
        // 创建NativeSdkManager
        that.initNativeSdkManager()
      })
    }
  }

  // 初始化C++通讯绑定函数
  if (typeof this.initNativeSdkManager !== 'function') {
    WebView.prototype.initNativeSdkManager = function () {
      // 创建失败和成功绑定函数
      NativeSdkManager.sucess.connect(this.onSuccess.bind(this))
      NativeSdkManager.failed.connect(this.onFailed.bind(this))
    }
  }

  /**
   * 获取webview
   * @params {string} webview.syberObject.key
   */
  if (typeof this.getWebView !== 'function') {
    WebView.prototype.getWebView = function (id) {
      var rwebview


      for (var i = 0; i < this._webviews.length; i++) {
        print('------this._webviews',JSON.stringify(this._webviews[i].syberObject),'\n')
        if (this._webviews[i].syberObject.key === id) {

          rwebview = this._webviews[i]
          break
        }
      }
      return rwebview
    }
  }

  /**
   * 获取当前webview数量
   */
  if (typeof this.size !== 'function') {
    WebView.prototype.size = function () {
      return this._webviews.length
    }
  }
  if (typeof this.create !== 'function') {
    WebView.prototype.create = function (_options, callback) {
      var defalutOption = {
        url: getIndexPath()
      }
      var key = 'webview_' + uuid()
      var options = Object.assign(defalutOption, _options)
      var that = this
      var component = Qt.createComponent('../qml/swebview.qml')
      var incubator = component.incubateObject(that._parent, {
        url: options.url,
        z: that.currentZ
      })

      this.currentZ = this.currentZ + 1
      if (incubator.status !== Component.Ready) {
        incubator.onStatusChanged = function (status) {
          if (status === Component.Ready) {
            var webview = incubator.object
            // 初始化完成再设置宽高
            webview.height = that._parent.height - 50
            webview.syberObject = {
              key: key
            }
            webview.width = that._parent.width - 30
            that._webviews.push(webview)
            // 做函数绑定
            webview.receiveMessage.connect(function (message) {
              that.onMessageReceived(message, key)
            })
            if (typeof callback === 'function') callback(webview)
          }
        }
      } else {
        console.error('Object', incubator.object, 'is ready immediately!')
      }
    }
  }

  /**
   * 消息接受
   * @params {JSON} 传输字符串
   * @parasm {string} webviewId
   */
  if (typeof this.onMessageReceived !== 'function') {
<<<<<<< HEAD
    WebView.prototype.onMessageReceived = function(message, webviewId) {
      console.log(
=======
<<<<<<< HEAD
    WebView.prototype.onMessageReceived = function (message, webviewId) {
      console.debug(
=======
    WebView.prototype.onMessageReceived = function(message, webviewId) {
      console.log(
>>>>>>> Revert "docs: 修复文档内示例代码资源引用不正确 (#4014)"
>>>>>>> hanagm-master
        '@@@ ',
        'WebView received Message: ',
         webviewId,
        JSON.stringify(message),
        '\r\n'
      )

      var model = JSON.parse(message.data)

      var handlerId = model.callbackId

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
        var keys = Object.keys(model.data)
        // 关联callbackId和webview

        for (var i in keys) {
          print('@@@ ', 'key: ', i, keys[i], '\r\n')
          print('@@@ value is', model.data[keys[i]])
          funcArgs[keys[i]] = model.data[keys[i]]
        }
      }

      NativeSdkManager.request(
        'TestHandler*',
        handlerId,
        model.handlerName,
        funcArgs
      )
    }
  }

  // 获取默认webview
  if (typeof this.getDefault !== 'function') {
    WebView.prototype.getDefault = function () {
      return this._webviews[0]
    }
  }

  // 获取所有webview
  if (typeof this.getAll !== 'function') {
    WebView.prototype.getAll = function () {
      return this._webviews
    }
  }

  /**
   * 根据请求ID获取对应webviewID
   * @param {string} responseId
   */
  if (typeof this.getWebViewIdByHandlerId !== 'function') {
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
      if(!webviewId){
         console.error('webview未找到')
         return;
      }
      delete this.responseCallbacks[handlerId]
      return webviewId
    }
  }

  /**
   *成功回调
   */
  if (typeof this.onSuccess !== 'function') {
    WebView.prototype.onSuccess = function (handlerId, result) {
      if (!handlerId) {
        return
      }
      var webviewId = this.getWebViewIdByHandlerId(handlerId)
      var webview = this.getWebView(webviewId)

      if(!webview){
        console.error("webview未找到")
          return;
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
  }
  if (typeof this.onFailed !== 'function') {
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
  }

  //默认初始化
 this.init();
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
