// 正常加载
var WebviewStatusShow = 0;
// 被pop打开
var WebviewStatusPop = 1;

var OnShowStautsReady = 'ready';
var OnShowStautsRedisplay = 'redisplay';

// 初次打开的页面
var HomePageUrl = '';

function WebView (options) {
  console.log('@@@@@@@@@ webview.js');
  // 默认参数
  var defaultOpts = {
    id: 'webview',
    name: 'webview',
    module: 'router',
    // source: '../qml/SWebview.qml',
    methods: ['reload', 'goBack', 'redirectTo', 'navigateTo', 'navigateBack', 'getCurrentPages', 'reLaunch', 'setTitle', 'setBackgroundColor', 'setNavigationBarColor', 'setPageOrientation'],
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

  that.loadComplete = false;

  this.on('ready', function (object) {
    logger.verbose('webview:[%s] ,on  ready() start', that.id, pageStack && pageStack.depth);
    logger.verbose('pageStack depth', pageStack && pageStack.depth);
    swebviewCache[that.id] = object;
    swebviews.push(that);
    currentWebview = that;

    // 添加onReady订阅(保证他是队列里的第一个)
    that.pushQueue('subscribe', {
      url: that.object.getCurrentUrl(),
      handlerName: 'onReady'
    });

    if (!that.loadProgressConnect) {
      // 设置绑定信号
      that.loadProgressConnect = true;
      // 页面加载成功信号
      object.sloadingChanged.connect(function (loadRequest) {
        var curUrl = loadRequest.url.toString();
        if (loadRequest.status === 2) {
          logger.verbose(' webview:[%s] ,页面加载完成 success: ', that.id, curUrl);
          // 调用任务狗
          that.dog(curUrl);
          that.loadComplete = true;
        }
      });

      // 关闭当前webview信号
      object.navigationBarClose.connect(function () {
        logger.info('navigationBarClose*********** %j', swebviews.length);
        if(swebviews.length == 1){
          Qt.quit();
          return;
        }
        that.trigger('navigateBack', object, null, { delta: 1 });
      });
    }

    // 屏幕旋转信号 (每个webview都监听了此信号，所以屏幕选择所有页面都会收到此消息)
    object.orientation.connect(function (orientationObj) {
      logger.verbose('orientationObj*********** %j', orientationObj);

      that.pushQueue('subscribe', {
        url: orientationObj.url,
        handlerName: 'onResize',
        result: {
          pageOrientation: orientationObj.pageOrientation,
          appOrientation: orientationObj.appOrientation
        }
      });
      if (that.loadComplete) {
        that.dog(orientationObj.url);
      }
    });

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
      
      // 第一次的时候,获取url地址
      HomePageUrl = swebviews[0].object.getCurrentUrl();
    }

    // 绑定消息接受信号
    object.receiveMessage.connect(function (message) {
      that.onMessageReceived(message, that.id);
    });
    // 绑定keys监听事件
    object.skeyEvent.connect(function (eventType, event) {
      logger.verbose(' webview.skeyEvent:[%s, %s]', eventType, that.id);
      that.trigger('keyEvent', object, eventType, event);
    });

    NativeSdkManager.request('DevTools*', 12378, '', {});
    NativeSdkManager.request('Packages*', 151010, '', {});
  });

  // 页面被打开
  this.on('show', function (options) {
    logger.verbose('Webivew:[%s] , on show() ,status:[%d]', that.id, options.status);
    // 页面被pop唤起,注销上一级页面
    if (options.status === WebviewStatusPop) {
      logger.verbose('Webivew:[%s] ,当前打开方式为pop，开始注销上一层', that.id, options.status);
    }
    that.pushQueue('subscribe', {
      url: options.url,
      handlerName: 'onShow'
    });

    that.dog(options.url);

    // 页面回到到上个页面，需要重置状态栏 1: 竖屏 2: 横屏 8: 横屏反向
    var orientation = that.object.orientationPolicy;
    var appOrientation = gScreenInfo.currentOrientation;
    var statusBarHoldEnabled = that.object.statusBarHoldEnabled;

    logger.verbose('当前屏幕方向: ', orientation, appOrientation, statusBarHoldEnabled);

    if (orientation == 1 || orientation == 0 && appOrientation == 1) {
      gScreenInfo.setStatusBar(true);
      if (!statusBarHoldEnabled) {
        statusBarHoldEnabled = true;
      }
    } else if (orientation == 2 || orientation == 8 ||
      orientation == 0 && (appOrientation == 2 || appOrientation == 8)) {
      gScreenInfo.setStatusBar(false);
      if (statusBarHoldEnabled) {
        statusBarHoldEnabled = false;
      }
    }
  });

  /**
   * 页面隐藏
   * (navigateTo 会触发)
   */
  this.on('hide', function () {
    logger.verbose('Webivew:, hide');

    that.pushQueue('subscribe', {
      url: that.object.getCurrentUrl(),
      handlerName: 'onHide'
    });

    that.dog(that.object.getCurrentUrl());
  });

  this.on('getCurrentPages', function (object, handlerId, param) {
    logger.verbose('on getCurrentPages()', handlerId);
    var depth = pageStack.depth || 1;
    that.trigger('success', handlerId, { depth: depth });
  });

  /**
   * 监听手机key
   */
  this.on('keyEvent', function (webview, eventType, event) {
    logger.verbose('webview:[%s] , on keyEvent(%s) ,key:[%s] ,currentWebview: [%s]', that.id, eventType, event.key, currentWebview.id);
    // 处理返回键事件
    if (KEYCODE_BACK === event.key) {
      logger.verbose('返回事件 | webview:[%s] | 是否能回退:[%s]:', that.id, webview.canGoBack());
      if (currentWebview.id === that.id && webview.canGoBack()) {
        event.accepted = true;
        that.trigger('unload', { url: webview.getCurrentUrl() });
        webview.goBack();
        if (!webview.canGoBack() && swebviews.length == 1) {
          webview.navigationBarBackIconEnable = false;
        }
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

    var curUrl = that.object.getCurrentUrl()

    that.pushQueue('subscribe', {
      url: curUrl,
      handlerName: 'onKeyEvent',
      result: {
        type: eventType,
        value: event.key
      }
    });

    that.dog(curUrl);
  });

  // 接受qml成功返回
  this.on('success', function () {
    logger.verbose('webview:[%s], on success()', that.id);
    var len = arguments.length;
    var funcArgs = [];
    for (var sum = 0; sum < len; sum += 1) {
      funcArgs.push(arguments[sum]);
    }
    logger.verbose('webview on success() funcArgs: %j', funcArgs);

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
    logger.verbose('Webivew:[%s] , on setTitle() ,param:%j', that.id, param);
    logger.verbose('---Webivew NavigationBar visible---', object.getNavigationBarStatus());

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

  // 设置导航栏颜色和字体颜色
  this.on('setNavigationBarColor', function (object, handlerId, param) {
    logger.verbose('Webivew:[%s] , on setNavigationBarColor() ,param:%j', that.id, param);
    logger.verbose('---Webivew NavigationBar visible---', object.getNavigationBarStatus());

    // 导航栏visible为false，不让修改标题
    if (!object.getNavigationBarStatus()) {
      that.trigger('failed', handlerId, 9002, '页面未设置导航栏，无法更改导航栏属性');
      return;
    }

    param.color = param.color.trim();
    param.backgroundColor = param.backgroundColor.trim();

    if (!param.color && !param.backgroundColor) {
      that.trigger('failed', handlerId, 9001, '参数不能为空');
      return;
    }

    object.setNavigationBarColor({
      color: param.color,
      backgroundColor: param.backgroundColor
    });

    that.trigger('success', handlerId, true);
  });

  // 设置背景色
  this.on('setBackgroundColor', function (object, handlerId, param) {
    logger.verbose('Webivew:[%s] , on setBackgroundColor() ,param:%j', that.id, param);

    param.backgroundColor = param.backgroundColor.trim();
    if (!param.backgroundColor) {
      that.trigger('failed', handlerId, 9001, 'backgroundColor不能为空');
      return;
    }
    object.setBackgroundColor(param.backgroundColor);
    that.trigger('success', handlerId, true);
  });
  // 保留当前页面，跳转到某个页面
  this.on('navigateBack', function (object, handlerId, param) {
    logger.verbose('Webview:[%s],on navigateBack() start', that.id);
    logger.verbose('handlerId:%s ,param:%j', handlerId, param);
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

  // 关闭所有页面，打开某个页面 (相当于redirectTo，让第一个webview打开url,成功后吧webview返回到顶层)
  this.on('reLaunch', function (object, handlerId, param) {
    logger.verbose('webview:[%s] on reLaunch %j', that.id, param);
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
          // 触发页面卸载方法(因为相当于redirectTo，所以取surl属性就是前一个页面的值)
          that.navigateBack({ delta: webviewMaxDepth }, function (res, webview, msg) {
            logger.verbose('reLaunch navigateBack()', res, msg);
            if (res) {
              logger.verbose('pageStack.busy:[%s]', pageStack.busy);
            }
          });

          if (param.backgroundColor) {
            currentWebview.object.setBackgroundColor(param.backgroundColor);
          }

          if (param.orientation) {
            currentWebview.object.setPageOrientation(param.orientation);
          }

          if (param.navigationBar) {
            var params = getNavigateBarParams(param.navigationBar);
            logger.verbose('navigationBar params***** %j', params);
            currentWebview.object.showNavigatorBar(params);
          }
        }
      });
    } catch (error) {
      logger.error('reLaunch error', error.message);
      that.trigger('failed', handlerId, 9999, error.message);
    }
  });
  // 保留当前页面，跳转到某个页面
  this.on('navigateTo', function (object, handlerId, param) {
    logger.verbose('webview:[%s] on navigateTo %j', that.id, param);
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
      // 根据 moduleVersion 中设定的版本使用不同的webview
      var sourceQml = '';
      switch(SYBEROS.moduleVersion){
        case '2':
          sourceQml = '../os2/SWebview.qml'
          break;
        case '5':
          sourceQml = '../os5/SWebview.qml'
          break;
        default:
          sourceQml = '../os4/SWebview.qml'
          break;
      }
      dwevview = new WebView({
        id: wpId,
        module: wpId,
        source: sourceQml,
        autoCreate: true,
        removePlugin: true,
        page: true
      });
      
      // 通过第一个页面的方向来判断全局页面的方向(因为第一个页面方向无法通过navigateTo跳转带上方向)
      var orientationPolicy =  swebviews[0].object.getPageOrientation();
      var orientation = param.orientation;

      if (orientation != undefined) {
        if (orientation == 0 || orientation == 1 || orientation == 2 || orientation == 8) {
          orientationPolicy = orientation;
        } else {
          that.trigger('failed', that.handlerId, 9001, 'orientation参数有误');
          return;
        }
      }

      logger.verbose('跳转新页面，设置横竖屏******', orientationPolicy);

      dwevview.param = {
        surl: getUrl(param.url),
        orientationPolicy: orientationPolicy,
        backgroundColor: param.backgroundColor
      };

      if (orientationPolicy == 2) {
        dwevview.param.statusBarHoldEnabled = false;
        gScreenInfo.setStatusBar(false);
      } else if (orientationPolicy == 1) {
        dwevview.param.statusBarHoldEnabled = true;
        gScreenInfo.setStatusBar(true);
      }

      // navigationBar参数
      if (param.navigationBar) {
        for (var key in param.navigationBar) {
          var newKey = 'navigationBar' + key.substring(0, 1).toUpperCase() + key.substring(1);
          logger.verbose('newKey-', newKey);
          dwevview.param[newKey] = param.navigationBar[key];
        }
        logger.verbose('dwevview.param-- %j', dwevview.param);
      }

      logger.verbose('webviewParams:%j', dwevview.param);

      dwevview.currentUrl = param.url;
      logger.verbose('navigator TO URL:-------------------', that.currentUrl);
      SYBEROS.addPlugin(dwevview);
      // 设定webview的深度为2
      webviewdepth += 1;
    }
    logger.verbose('helper.isGtQt56--', helper.isGtQt56());
    that.trigger('success', handlerId, true);

    that.trigger('hide');
  });

  // 不关闭当前页面，跳转到某个页面
  this.on('redirectTo', function (object, handlerId, param) {
    try {
      logger.verbose('webview:[%s] on redirectTo %j', that.id, param);
      logger.verbose('页面redirectTo*********卸载页面*****', currentWebview.object.getCurrentUrl());
      var curUrl = currentWebview.object.getCurrentUrl();
      var url = getUrl(param.url);
      currentWebview.object.openUrl(url);
      currentWebview.trigger('success', handlerId, true);
      currentWebview.trigger('unload', { url: curUrl });

      if (param.backgroundColor) {
        currentWebview.object.setBackgroundColor(param.backgroundColor);
      }

      if (param.orientation) {
        currentWebview.object.setPageOrientation(param.orientation);
      }

      if (param.navigationBar) {
        var params = getNavigateBarParams(param.navigationBar);
        logger.verbose('navigationBar params***** %j', params);
        currentWebview.object.showNavigatorBar(params);
      }

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
   * 页面卸载
   * (如redirectTo或navigateBack或reLaunch到其他页面时)
   */
  this.on('unload', function (options) {
    logger.verbose('页面要卸载了unload****** %j', options);

    var curUrl = options.url;
    // 发送onUnload事件
    that.pushQueue('subscribe', {
      url: curUrl,
      handlerName: 'onUnload'
    });

    that.dog(curUrl);
  });

  // 设置屏幕旋转方向
  this.on('setPageOrientation', function (object, handlerId, param) {
    logger.verbose('Webivew:[%s] , on setPageOrientation() ,param:%j ,', that.id, param, typeof that.param.orientation);
    var orientation = that.param.orientation;

    object.setPageOrientation(param.orientation);
    // 不能从qml里面发信号（因为手机没有开屏幕旋转，qml接收不到信号，所以不可依赖）
    that.trigger('success', handlerId, {
      pageOrientation: orientation,
      appOrientation: gScreenInfo.currentOrientation
    });
  });

  /**
   * 任务狗，用来处理队列中的消息
   */
  function dog (currentUrl) {
    logger.verbose('dog()', typeof currentUrl, currentUrl);
    var queue = this.messageQueue;
    logger.verbose('dog() 处理消息数:%d', queue.length);
    var len = queue.length;
    for (var i = 0; i < len; i++) {
      // 每次从头部拿到消息，并从队列删除
      var obj = queue.shift();
      if (!obj) {
        logger.verbose('消息内容:%j', obj);
        continue;
      }
      logger.verbose('消息内容:%j', obj);
      var dUrl = obj.url;

      var dret = diffUrl(currentUrl, dUrl);
      if (!dret) {
        // 如果不是当前页面的消息，再给他加到队列里面，等到了该页面继续推出去(考虑到redirectTo的情况)
        this.messageQueue.push(obj);
        logger.verbose('当前消息队列不匹配:%s', obj.url);
        continue;
      }
      if (obj.type === 'request') {
        if (obj.errorCode) {
          this.trigger('fail', obj.handlerId, obj.result);
        }
        this.trigger('success', obj.handlerId, obj.result);
      }
      if (obj.type === 'subscribe') {
        this.subscribeEvaluate(obj.handlerName, obj.result);
      }
      logger.verbose('dog() queue length:', queue.length);
    }
  }
  /**
   * 存入队列任务
   * @param {string} type 消息类型 request,subscribe
   * @param {Object} object 消息构造体 {result,handlerName||handlerId}
   */
  function pushQueue (type, object) {
    logger.verbose('pushQueue() type:%s ,content:%j', type, object);
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
    logger.verbose('pushQueue() type:%s, content:%j', type, obj);
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
          logger.verbose('连续返回多个webview****************', dwebview.object.getCurrentUrl());
          // 用dwebview代表被卸载的webview
          dwebview.trigger('unload', { url: dwebview.object.getCurrentUrl() });
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
      topVebview.trigger('show', {
        status: WebviewStatusPop,
        url: topVebview.currentUrl ? topVebview.currentUrl : topVebview.object.surl
      });
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
  logger.verbose('webview:[%s] ,onMessageReceived(): ', webviewId, typeof message, typeof message.data, message);

  var model;
  if (message && typeof message === 'object') {
    model = JSON.parse(message.data);
  } else {
    model = JSON.parse(message);
  }

  logger.verbose('**********model********** %j', model);

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
    logger.verbose('onMessageReceived() currentWebview.module: %j', currentWebview.module);
    module = currentWebview.module;
    logger.verbose('onMessageReceived() laset module ', module);
  } else if (module === 'packages') {
    // 如果是packages模块,发送消息的页面在这里进行修改
    var urlArr = HomePageUrl.split('/')
    funcArgs.path = urlArr[urlArr.length-1]
    logger.verbose('packages****funcArgs**** %j', funcArgs)
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
    responseId: Number(handlerId),
    responseData: {
      result: result
    }
  };
  logger.verbose('Webview onSuccess() return: %j', resObj);

  var webview = msgWebview.object;
  webview.evaluateJavaScript(resObj);
};

WebView.prototype.onSubscribe = function (handlerName, result) {
  logger.verbose('Webview:%s onSubscribe() start  handlerName:%s, result:%j', this.id, handlerName, result);
  if (handlerName === 'DevToolsReload') {
    for (var i in swebviews) {
      swebviews[i].trigger('reload', swebviews[i].object);
    }
    return;
  }

  // 第2个APP被唤起的时候，监听的onReady事件,消息推送到HomePageUrl页面
  if (handlerName === 'package') {
    this.pushQueue('subscribe', {
      handlerName: 'onReady',
      url: HomePageUrl,
      result: result
    });
    
    // 每次进来都是首页,重新加载, 在ready事件中,页面加载到100%的时候,会dog一下,onReady事件就触发了
    swebviews[0].object.reload();
    return;
  }

  var resObj = {
    handlerName: handlerName,
    data: {
      result: result
    }
  };
  logger.verbose('onSubscribe() res: %j', resObj);
  var webview = this.object;
  webview.evaluateJavaScript(resObj);
};

WebView.prototype.subscribeEvaluate = function (handlerName, data) {
  logger.verbose('Webview:%s subscribeEvaluate () start', this.id);
  var resObj = {
    handlerName: handlerName,
    data: data
  };
  logger.verbose('subscribeEvaluate() res: %j', resObj);

  var webview = this.object;
  webview.evaluateJavaScript(resObj);
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

  var resObj = {
    responseId: Number(handlerId),
    responseData: {
      code: Number(errorCode),
      msg: errorMsg
    }
  };
  logger.verbose('onFailed() res: %j', resObj);
  webview.evaluateJavaScript(resObj);
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

/**
 * 转换navigateBar的参数
 */
function getNavigateBarParams (params) {
  var obj = {};
  for (var key in params) {
    var newKey = 'navigationBar' + key.substring(0, 1).toUpperCase() + key.substring(1);
    logger.verbose('newKey-', newKey);
    obj[newKey] = params[key];
  }
  return obj;
}
