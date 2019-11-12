// 正常加载
var WebviewStatusShow = 0;
// 被pop打开
var WebviewStatusPop = 1;

function WebView (options) {
  // 默认参数
  var defaultOpts = {
    id: 'webview',
    name: 'webview',
    module: 'router',
    // source: '../qml/SWebview.qml',
    methods: ['reload', 'goBack', 'redirectTo', 'navigateTo', 'navigateBack', 'getCurrentPages', 'reLaunch', 'setTitle', 'setBackgroundColor', 'setNavigationBarColor'],
    autoCreate: true
  };
  if (options) {
    Object.assign(defaultOpts, options);
  }

  SyberPlugin.call(this, defaultOpts);
  // 当前url
  this.currentUrl = null;
  this.key = 0;
  // 是否加载成功
  this.loadSuccessEvent = 0;
  // 是否绑定LoadProgress 信号
  this.loadProgressConnect = false;
  // 消息队列,用来处理loadSuccess消息
  this.messageQueue = [];
  var that = this;
  // 回退
  this.navigateBack = navigateBack.bind(this);
  this.dog = dog.bind(this);
  this.pushQueue = pushQueue.bind(this);

  this.on('ready', function (object) {
    logger.verbose('webview:[%s] ,on  ready() start', that.id, pageStack && pageStack.depth);
    logger.verbose('pageStack depth', pageStack && pageStack.depth);
    swebviewCache[that.id] = object;
    swebviews.push(that);
    currentWebview = that;
    if (that.currentUrl) {
      logger.verbose('currentUrl:', that.currentUrl);
      // 发送onShow订阅
      that.pushQueue('subscribe', {
        url: that.currentUrl,
        handlerName: 'onShow',
        result: { ready: true }
      });
    }
    if (!that.loadProgressConnect) {
      // 设置绑定信号
      that.loadProgressConnect = true;
      // 页面加载成功信号
      object.sloadingChanged.connect(function (loadRequest) {
        if (loadRequest.status === 2) {
          logger.verbose(' webview:[%s] ,页面加载完成 success: ', that.id, loadRequest.url.toString());
          // 调用任务狗
          that.dog(loadRequest.url.toString());
        }
      });

      // 关闭当前webview信号
      object.navigationBarClose.connect(function () {
        that.trigger('navigateBack', object, null, { delta: 1 });
      });
    }
    // 只保证一个webview注册nativesdk
    if (!registrNativeSdkManager) {
      registrNativeSdkManager = true;
      logger.verbose('on ready registrNativeSdkManager:[%s]', registrNativeSdkManager);
      // 成功回调绑定函数
      NativeSdkManager.success.connect(that.onSuccess.bind(that));
      // 错误回调绑定函数
      NativeSdkManager.failed.connect(that.onFailed.bind(that));
      // 绑定订阅函数
      NativeSdkManager.subscribe.connect(that.onSubscribe.bind(that));

      logger.verbose('on ready registrNativeSdkManager:[%s] 绑定完成', registrNativeSdkManager);
    }

    // 绑定消息接受信号
    object.receiveMessage.connect(function (message) {
      that.onMessageReceived(message, that.id);
    });
    // 绑定keys监听事件
    object.keyOnReleased.connect(function (event) {
      logger.verbose(' webview.keyOnReleased:[%s]', that.id);
      that.trigger('keyRelease', object, event);
    });

    NativeSdkManager.request('DevTools*', 12378, '', '');
    NativeSdkManager.request('Package*', 151010, '', '');
  });

  // 页面被打开
  this.on('show', function (status) {
    logger.verbose('Webivew:[%s] , on show() ,status:[%d]', that.id, status);
    // 页面被pop唤起,注销上一级页面
    if (status === WebviewStatusPop) {
      logger.verbose('Webivew:[%s] ,当前打开方式为pop，开始注销上一层', that.id, status);
    }
  });

  this.on('hide', function () {

  });

  this.on('getCurrentPages', function (object, handlerId, param) {
    logger.verbose('on getCurrentPages()', handlerId);
    var depth = pageStack.depth || 1;
    that.trigger('success', handlerId, { depth: depth });
  });

  /**
   * 监听手机key
   */
  this.on('keyRelease', function (webview, event) {
    logger.verbose('webview:[%s] , on keyRelease() ,key:[%s] ,currentWebview: [%s]', that.id, event.key, currentWebview.id);
    // 处理返回键事件
    if (KEYCODE_BACK === event.key) {
      logger.verbose('返回事件 | webview:[%s] | 是否能回退:[%s]:', that.id, webview.canGoBack());
      if (currentWebview.id === that.id && webview.canGoBack()) {
        event.accepted = true;
        webview.goBack();
      } else {
        that.navigateBack({}, function (res) {
          if (res) {
            // 阻止回退事件
            if (event) {
              event.accepted = true;
            }
          }
        });
        logger.verbose('webview:[%s] 不能回退:[%s]', that.id, webview.canGoBack());
      }
    }
  });

  // 接受qml成功返回
  this.on('success', function () {
    logger.verbose('webview:[%s], on success()', that.id);
    var len = arguments.length;
    var funcArgs = [];
    for (var sum = 0; sum < len; sum += 1) {
      funcArgs.push(arguments[sum]);
    }
    logger.verbose('webview on success() funcArgs:', JSON.stringify(funcArgs));

    that.onSuccess.apply(this, funcArgs);
  });
  // 接受qml组件fail返回
  this.on('failed', function () {
    logger.verbose('webview on failed()');
    var len = arguments.length;
    var funcArgs = [];

    for (var sum = 0; sum < len; sum += 1) {
      funcArgs.push(arguments[sum]);
    }
    that.onFailed.apply(this, funcArgs);
  });

  /**
   * request 请求
   * @object qml实例化对象
   * @handlerId 请求ID
   * @param 请求参数
   * @method 请求方法名称
   */
  this.on('reload', function (object, handlerId) {
    logger.verbose('webview:[%s]  ,on reload()', that.id);
    try {
      object.reload();
      logger.verbose('webview:[%s]  ,on reload() success');
      that.trigger('success', handlerId, true);
    } catch (e) {
      logger.verbose('webview:[%s]  ,on reload() failed');
      that.trigger('failed', handlerId, 2006, false);
    }
  });
  // 回退
  this.on('goBack', function (object, handlerId) {
    logger.verbose('webview:[%s] on goBack()', that.id);
    if (object.canGoBack()) {
      logger.verbose('object.canGoBack', object.canGoBack());
      object.goBack();
      that.trigger('success', handlerId, true);
    } else {
      that.trigger('failed', handlerId, 2007, false);
    }
  });

  // 给页面设置标题
  this.on('setTitle', function (object, handlerId, param) {
    console.log('Webivew:[%s] , on setTitle() ,param:%s ,', that.id, JSON.stringify(param));
    console.log('---Webivew NavigationBar visible---', object.getNavigationBarStatus());

    // 导航栏visible为false，不让修改标题
    if (!object.getNavigationBarStatus()) {
      that.trigger('failed', handlerId, 9002, '页面未设置导航栏，无法更改导航栏标题');
      return;
    }

    param.title = param.title.trim();

    if (!param.title) {
      that.trigger('failed', handlerId, 9001, 'title不能为空');
      return;
    }

    if (param.title && param.title.length > 8) {
      that.trigger('failed', handlerId, 9001, '标题最多8个汉字');
      return;
    }

    object.setNavigationBarTitle(param.title);
    that.trigger('success', handlerId, true);
  });

  // 设置标题
  this.on('setTitle', function (object, handlerId, param) {
    console.log('Webivew:[%s] , on setTitle() ,param:%s ,', that.id, JSON.stringify(param));
    console.log('---Webivew NavigationBar visible---', object.getNavigationBarStatus());

    // 导航栏visible为false，不让修改标题
    if (!object.getNavigationBarStatus()) {
      that.trigger('failed', handlerId, 9002, '页面未设置导航栏，无法更改导航栏属性');
      return;
    }

    param.title = param.title.trim();

    if (!param.title) {
      that.trigger('failed', handlerId, 9001, 'title不能为空');
      return;
    }

    if (param.title && param.title.length > 8) {
      that.trigger('failed', handlerId, 9001, '标题最多8个汉字');
      return;
    }

    object.setNavigationBarTitle(param.title);
    that.trigger('success', handlerId, true);
  });

  // 设置导航栏颜色和字体颜色
  this.on('setNavigationBarColor', function (object, handlerId, param) {
    console.log('Webivew:[%s] , on setNavigationBarColor() ,param:%s ,', that.id, JSON.stringify(param));
    console.log('---Webivew NavigationBar visible---', object.getNavigationBarStatus());

    // 导航栏visible为false，不让修改标题
    if (!object.getNavigationBarStatus()) {
      that.trigger('failed', handlerId, 9002, '页面未设置导航栏，无法更改导航栏属性');
      return;
    }

    param.color = param.color.trim();
    param.textColor = param.textColor.trim();

    if (!param.color && !param.textColor) {
      that.trigger('failed', handlerId, 9001, '参数不能为空');
      return;
    }

    object.setNavigationBarColor({
      color: param.color,
      textColor: param.textColor
    });

    that.trigger('success', handlerId, true);
  });

  // 设置背景色
  this.on('setBackgroundColor', function (object, handlerId, param) {
    logger.verbose('Webivew:[%s] , on setBackgroundColor() ,param:%s ,', that.id, JSON.stringify(param));
    console.log('Webivew:[%s] , on setBackgroundColor() ,param:%s ,', that.id, JSON.stringify(param));

    param.color = param.color.trim();
    if (!param.color) {
      that.trigger('failed', handlerId, 9001, 'color不能为空');
      return;
    }
    object.setBackgroundColor(param.color);
    that.trigger('success', handlerId, true);
  });
  // 保留当前页面，跳转到某个页面
  this.on('navigateBack', function (object, handlerId, param) {
    logger.verbose('Webview:[%s],on navigateBack() start', that.id);
    logger.verbose('handlerId:%s ,param:', that.id, handlerId, JSON.stringify(param));
    if (!isNumber(param.delta)) {
      var msg = 'delta参数类型错误';
      that.trigger('fail', 6004, msg);
      return;
    }
    that.navigateBack(param, function (res, msg) {
      if (!handlerId) {
        return;
      }
      if (res) {
        that.trigger('success', handlerId, res);
      } else {
        that.trigger('fail', 9999, msg);
      }
    });
  });

  // 关闭所有页面，打开某个页面
  this.on('reLaunch', function (object, handlerId, param) {
    logger.verbose('webview:[%s] on reLaunch', that.id, JSON.stringify(param));
    logger.verbose('reLaunch swebviews:[%d]', swebviews.length);
    logger.verbose('webviewdepth:[%d]', webviewdepth);

    try {
      var url = getUrl(param.url);
      swebviews[0].object.openUrl(url);
      swebviews[0].object.sloadingChanged.connect(function (loadRequest) {
        // 加载完成后关闭上层界面，防止进程崩溃
        if (loadRequest.status === 2) {
          logger.verbose(' webview:[%s] ,页面加载完成 success: ', that.id, loadRequest.url.toString());
          currentWebview.trigger('success', handlerId, true);
          that.navigateBack({ delta: webviewMaxDepth }, function (res, webview, msg) {
            logger.verbose('reLaunch navigateBack()', res, msg);
            if (res) {
              logger.verbose('pageStack.busy:[%s]', pageStack.busy);
            }
          });
        }
      });
    } catch (error) {
      logger.error('reLaunch error', error.message);
      that.trigger('failed', handlerId, 9999, error.message);
    }
  });
  // 保留当前页面，跳转到某个页面
  this.on('navigateTo', function (object, handlerId, param) {
    logger.verbose('webview:[%s] on navigateTo', that.id, JSON.stringify(param));
    logger.verbose('navigateTo swebviews:[%d]', swebviews.length);
    logger.verbose('webviewdepth:[%d]', webviewdepth);
    var dwevview = null;
    // 如果已经是最大栈,则使用底层栈
    if (webviewdepth + 1 > webviewMaxDepth) {
      // TODO: 为了防止层数过多卡死,暂不支持使用最新页面
      // var idx = getUpperWebview()
      // logger.verbose('当前为最多栈数,使用历史栈:[%d]', idx)
      // dwevview = swebviews[idx]
      // webviewdepth += 1
      // SYBEROS.request(dwevview.module, handlerId, 'redirectTo', param)
      var ret = '页面栈层数已到最大';
      that.trigger('failed', handlerId, 9005, ret);
      return;
    } else {
      var wpId = 'router_' + (swebviews.length + 1);
      logger.verbose('开始创建新的webview:[%s]', wpId);
      dwevview = new WebView({
        id: wpId,
        module: wpId,
        source: '../qml/SWebview.qml',
        autoCreate: true,
        removePlugin: true,
        page: true
      });
      dwevview.param = {
        surl: getUrl(param.url)
      };

      // webview参数
      if (param.webview) {
        for (var key in param.webview) {
          dwevview.param[key] = param.webview[key];
        }
        console.log('dwevview.param--', JSON.stringify(dwevview.param));
      }

      // navigationBar参数
      if (param.navigationBar) {
        for (var key in param.navigationBar) {
          var newKey = 'navigationBar' + key.substring(0, 1).toUpperCase() + key.substring(1);
          console.log('newKey-', newKey);
          dwevview.param[newKey] = param.navigationBar[key];
        }
        console.log('dwevview.param--', JSON.stringify(dwevview.param));
      }

      logger.verbose('webviewParams:[%s]', JSON.stringify(dwevview.param));
      console.log('webviewParams:[%s]', JSON.stringify(dwevview.param));

      dwevview.currentUrl = param.url;
      SYBEROS.addPlugin(dwevview);
      // 设定webview的深度为2
      webviewdepth += 1;
    }
    that.trigger('success', handlerId, true);
  });

  // 不关闭当前页面，跳转到某个页面
  this.on('redirectTo', function (object, handlerId, param) {
    try {
      logger.verbose('webview:[%s] on redirectTo', that.id, JSON.stringify(param));
      var url = getUrl(param.url);
      currentWebview.object.openUrl(url);
      currentWebview.trigger('success', handlerId, true);
      if (handlerId) {
        that.trigger('success',
          handlerId,
          true
        );
      }
    } catch (error) {
      logger.error('redirectTo error', error.message);
      that.trigger('failed', handlerId, 9999, error.message);
    }
  });
  /**
   * 任务狗，用来处理队列中的消息
   */
  function dog (currentUrl) {
    logger.verbose('dog()', typeof currentUrl);
    var queue = this.messageQueue;
    logger.verbose('dog() 处理消息数:%d', queue.length);
    for (var i = 0; i < queue.length; i++) {
      var obj = queue[i];
      logger.verbose('消息内容:%s', JSON.stringify(obj));
      var dUrl = obj.url;
      var dret = diffUrl(currentUrl, dUrl);
      if (!dret) {
        logger.verbose('当前消息队列不匹配:%s', obj.url);
        continue;
      }
      if (obj.type === 'request') {
        if (obj.errorCode) {
          this.trigger('fail', obj.handlerId, obj.result);
        }
        this.trigger('success', obj.handlerId, obj.result);
        continue;
      }
      if (obj.type === 'subscribe') {
        this.subscribeEvaluate(obj.handlerName, obj.result);
        continue;
      }
      queue.splice(i, 1);
    }
  }
  /**
   * 存入队列任务
   * @param {string} type 消息类型 request,subscribe
   * @param {Object} object 消息构造体 {result,handlerName||handlerId}
   */
  function pushQueue (type, object) {
    logger.verbose('pushQueue() type:%s ,content:%s', type, JSON.stringify(object));
    var obj = {};
    // 合并相同任务
    if (object.handlerName === 'subscribe') {
      var queue = this.messageQueue;
      var same = false;
      for (var i = 0; i < queue.length; i++) {
        var handlerName = object.handlerName;
        if (handlerName === queue[i].handlerName) {
          logger.verbose('存在相同的handlerName', handlerName);
          if (isObject(object.result)) {
            same = true;
            var nresult = Object.assign(object.result, queue[i].result);
            var nobj = Object.assign({}, queue[i], nresult);
            queue.splice(i, 1, nobj);
            break;
          } else {
            logger.verbose('object.result 不是object,不做合并处理', handlerName);
          }
        }
      }
      if (!same) {
        Object.assign(obj, object, { type: type });
        this.messageQueue.push(obj);
        return;
      }
    }
    Object.assign(obj, object, { type: type });
    logger.verbose('pushQueue() content:%s', type, JSON.stringify(obj));
    this.messageQueue.push(obj);
  }

  /**
   * 回退方法
   * @param {object} param 参数
   * @param {function} callback 回调方法
   */
  function navigateBack (param, callback) {
    logger.verbose('webview navigateBack() 当前页面栈数: [ %d ]', swebviews.length);
    logger.verbose('webview navigateBack() 栈的深度: [ %d ]', pageStack.depth);
    var delta = param && param.delta || 1;
    var reLaunch = false;
    // 如果当前有多个weview,则减少栈数
    if (swebviews.length > 1) {
      // 如果 delta 大于现有页面数，则返回首页
      if (delta >= swebviews.length) {
        reLaunch = true;
        // 去除的层数
        delta = swebviews.length - 1;
        logger.verbose('delta数大于或者当前栈,处理完结果为: [ %d ]', delta);
      }
      logger.verbose('navigateBack() delta: [ %d ]', delta);
      for (var j = 0; j < delta; j++) {
        // 从后面层数获取
        // var ds = swebviews.length - 1;
        logger.verbose('navigateBack() ds: [ %d ]', j);
        // var idx = getLowerWebview()
        var dwebview = swebviews.pop();
        webviewdepth -= 1;
        // dwebview.trigger('show', WebviewStatusPop)
        if (dwebview) {
          // 开始注销
          logger.verbose('Webivew:[%s] , 开始destroy', dwebview.id);
          SYBEROS.destroy(dwebview.id);
          logger.verbose('Webivew:[%s] , destroy完成 ,当前数量: %d', dwebview.id, swebviews.length);
        }
      }
      var topVebview = swebviews[swebviews.length - 1];
      currentWebview = topVebview;
      if (swebviews.length === 1) {
        logger.verbose('返回最顶层:[%d]', swebviews.length);
        pageStack.pop(topVebview.object);
      } else {
        pageStack.pop(topVebview.object);
      }
      logger.verbose('topVebview:[%s],当前swebviews数量: [%d],栈的深度: [%d]', topVebview.id, swebviews.length, pageStack.depth);
      topVebview.trigger('show', WebviewStatusPop);
      if (typeof callback === 'function') callback(true, topVebview, true);
    } else {
      logger.verbose('navigateBack() 当前页面栈数为: [ %d ],不做处理', swebviews.length);
      var msg = '当前为首页,无法退回';
      logger.verbose('navigateBack() msg:%s', msg);
      var topVebview = swebviews[swebviews.length - 1];
      if (typeof callback === 'function') callback(false, topVebview, msg);
    }
  }
}

WebView.prototype = SyberPlugin.prototype;

WebView.prototype.onMessageReceived = function (message, webviewId) {
  logger.verbose('webview:[%s] ,onMessageReceived(): ', webviewId, message);

  var model = message;
  if (typeof message === 'string') {
    model = JSON.parse(message);
  }
  var handlerId = model.callbackId;
  var method = model.handlerName;
  var module = model.module;

  // 如果有callbackId 则保存回调信息
  if (handlerId) {
    // 是否为长期回调
    var isLong = model['isLong'] || false;
    // 保存到短期中
    responseCallbacks[handlerId] = webviewId;
    if (isLong) {
      // 如果需要长期,则保存长期池
      responseCallbacksLongTerm[handlerId] = webviewId;
    }
  }
  var funcArgs = {};
  if (model.data) {
    funcArgs = model.data;
  }

  if (module === 'webview' || module === 'router') {
    logger.verbose(JSON.stringify(currentWebview.module));
    module = currentWebview.module;
    logger.verbose('onMessageReceived() laset module ', module);
  }

  // 如果为ui模块
  if (SYBEROS.getPlugin(module, method)) {
    // 请求qml动态模块
    SYBEROS.request(module, handlerId, method, model.data);
    return;
  }

  // 因为C++类都为大写开头,所以第一个字母转为大写
  var moduleName = module.charAt(0).toUpperCase() + module.slice(1) + '*';
  NativeSdkManager.request(moduleName, handlerId, method, funcArgs);
};

WebView.prototype.onSuccess = function (handlerId, result) {
  logger.verbose('webview:[%s] ,onSuccess() start', this.id, handlerId);
  if (!handlerId) {
    logger.warn('Webview onSuccess() handlerId is null');
    return;
  }
  var webviewId = this.getWebViewIdByHandlerId(handlerId);
  var msgWebview = this.getWebView(webviewId);

  if (!msgWebview) {
    logger.error('Webview onSuccess() webview %s 未找到', webviewId);
    return;
  }
  // 返回内容
  var resObj = {
    // handlerName:"handleError",
    responseId: Number(handlerId),
    responseData: {
      result: result
    }
  };
  var res = JSON.stringify(resObj);
  logger.verbose('Webview onSuccess() return', handlerId, res);

  var webview = msgWebview.object;
  webview.evaluateJavaScript(
    'JSBridge._handleMessageFromNative(' + res + ')'
  );
};

WebView.prototype.onSubscribe = function (handlerName, result) {
  logger.verbose('Webview:%s onSubscribe() start', this.id, handlerName, JSON.stringify(result));
  if (handlerName === 'DevToolsReload') {
    this.trigger('reload', this.object);
    return;
  }
  if (handlerName === 'onShow') {
    var params = {};
    params.url = result.path;
    this.pushQueue('subscribe', {
      handlerName: handlerName,
      url: result.path,
      result: result
    });
    this.trigger('redirectTo', this.object, null, params);

    return;
  }
  var resObj = {
    handlerName: handlerName,
    data: {
      result: result
    }
  };
  var res = JSON.stringify(resObj);
  logger.verbose('onSubscribe() res:', res);
  var webview = currentWebview.object;
  webview.evaluateJavaScript(
    'JSBridge._handleMessageFromNative(' + res + ')'
  );
};

WebView.prototype.subscribeEvaluate = function (handlerName, data) {
  logger.verbose('Webview:%s subscribeEvaluate () start', this.id);
  var resObj = {
    handlerName: handlerName,
    data: data
  };
  var res = JSON.stringify(resObj);
  logger.verbose('subscribeEvaluate() res:', res);
  var webview = currentWebview.object;
  webview.evaluateJavaScript(
    'JSBridge._handleMessageFromNative(' + res + ')'
  );
};

WebView.prototype.onFailed = function (handlerId, errorCode, errorMsg) {
  logger.verbose('Webview:%s , onFailed() start', this.id, handlerId, errorCode, errorMsg);
  if (!handlerId) {
    logger.warn('Webview onFailed() handlerId is null');
    return;
  }
  var webviewId = this.getWebViewIdByHandlerId(handlerId);
  var msgWebview = this.getWebView(webviewId);

  if (!msgWebview) {
    logger.error('Webview onFailed() webview %s 未找到', webviewId);
    return;
  }
  var webview = msgWebview.object;

  var obj = {
    responseId: Number(handlerId),
    responseData: {
      code: Number(errorCode),
      msg: errorMsg
    }
  };
  var res = JSON.stringify(obj);
  logger.verbose('onFailed() res: ', res);
  webview.evaluateJavaScript(
    'JSBridge._handleMessageFromNative(' + res + ')'
  );
};

WebView.prototype.getWebViewIdByHandlerId = function (handlerId) {
  logger.verbose('webview:[%s] , getWebViewIdByHandlerId()', this.id, handlerId);
  var webviewId = responseCallbacks[handlerId];
  // 默认先短期再长期
  webviewId = webviewId || responseCallbacksLongTerm[handlerId];
  logger.verbose('webviewId:', webviewId);
  if (!webviewId) {
    logger.error('getWebViewIdByHandlerId() webview未找到', webviewId);
    return;
  }
  delete responseCallbacks[handlerId];
  logger.verbose('getWebViewIdByHandlerId() end webviewId:[%s]', webviewId);
  return webviewId;
};

// 获取默认webview
WebView.prototype.getDefault = function () {
  return swebviewCache[0];
};

// 获取所有webview

WebView.prototype.getAll = function () {
  return swebviewCache;
};

WebView.prototype.getWebView = function (id) {
  var rwebview = currentWebview;
  if (id !== rwebview) {
    for (var i = 0; i < swebviews.length; i++) {
      if (id === swebviews[i].id) {
        rwebview = swebviews[i];
        break;
      }
    }
  }
  return rwebview;
};

/**
 * 获取默认html页面地址
 * @return {String}
 */
function getIndexPath () {
  var url = 'file://' + helper.getWebRootPath() + '/index.html';
  logger.verbose('getIndexPath()', url);
  return url;
}

/**
 * 获取上一层webview的索层
 * return {number} 上一层的索引层
 */
function getUpperWebview () {
  var idx;
  // 如果最顶层,则使用第二层,因为第一层是最初界面
  if (webviewdepth + 1 > webviewMaxDepth) {
    idx = 1;
  } else {
    idx = webviewdepth + 1;
  }
  logger.verbose('getUpperWebview() : [ %d ]', idx);
  return idx;
}
/**
 * 获取下一层webview的索层
 * return {number} 小一层的索引层
 */
function getLowerWebview () {
  var idx;
  if (webviewdepth === 0) {
    idx = 0;
  } else {
    idx = webviewdepth - 1;
  }
  logger.verbose('getLowerWebview() : [ %d ]', idx);
  return idx;
}
