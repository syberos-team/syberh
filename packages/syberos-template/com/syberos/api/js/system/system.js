/* eslint-disable no-undef */

/***
 * modal.alert(Object)
 */
function System () {
  var defaultOpts = {
    id: 'system',
    module: 'system',
    methods: ['aboutPhone'],
    source: ''
  }
  SyberPlugin.call(this, defaultOpts)

  // 是否第一次绑定接受信号
  this.firstConnect = false

  var that = this;
  this.on('aboutPhone', function (object, handlerId, param) {
    var component = object || that.object

    var info = helper.aboutPhone();
    info.statusBarHeight = gScreenInfo.statusBarHeight;
    info.windowWidth = gScreenInfo.displayWidth;
    info.windowHeight = gScreenInfo.displayHeight;

    // 只做一次信号绑定,防止多次信号被触发
    if(!that.firstConnect) {
        // 设置绑定信号
        that.firstConnect = true;

        // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
        WEBVIEWCORE.trigger('success', that.handlerId, info);
    }
  });
}

System.prototype = SyberPlugin.prototype
