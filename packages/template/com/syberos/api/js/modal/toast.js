/* eslint-disable no-undef */

/***
 * modal.toast(Object)
 */
function Toast () {
  var defaultOpts = {
    id: 'toast',
    name: 'toast',
    module: 'modal',
    methods: ['toast'],
    source: '../qml/SToast.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this

  this.on('toast', function (object, handlerId, param) {
    var component = object
    if(!component){
       that.failed(that.handlerId, 6002, "组件初始化错误");
    }
    var ret = component.show(that.param.title, that.param.icon, that.param.duration);
    if(ret){
        logger.verbose('component.show ret:',ret)
        that.failed(that.handlerId, 6001, ret);
        return;
    }
    // 确认事件
    component.accepted.connect(function() {
      // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
      that.success(that.handlerId);
    });
  });
}

Toast.prototype = SyberPlugin.prototype
