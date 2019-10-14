/* eslint-disable no-undef */

/***
 * modal.alert(Object)
 */
function System () {
  var defaultOpts = {
    id: 'system',
    module: 'system',
    methods: ['aboutPhone']
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this;
  this.on('aboutPhone', function (object, handlerId, param) {
    var component = object || that.object

    var info = helper.aboutPhone();
    info.statusBarHeight = gScreenInfo.statusBarHeight;
    info.windowWidth = gScreenInfo.displayWidth;
    info.windowHeight = gScreenInfo.displayHeight;

    // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
    WEBVIEWCORE.trigger('success', that.handlerId, info);
  });
}

System.prototype = SyberPlugin.prototype
