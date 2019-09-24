/* eslint-disable no-undef */

/***
 * modal.toast(Object)
 */
function Toast () {
  var defaultOpts = {
    id: 'toast',
    name: 'toast',
    module: 'modal',
    methods: ['toast','gtoast'],
    source: '../qml/SToast.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this
  this.on('gtoast',function(){
    if(!that.param.title){
        WEBVIEWCORE.trigger( 'failed', that.handlerId, 1003, "提示的内容不能为空");
        return;
    }
    gToast.requestToast(that.param.title);
    WEBVIEWCORE.trigger('success',that.handlerId);
  });

  this.on('toast', function (object, handlerId, param) {
    var component = object || that.object

    var ret = component.show(that.param.title, that.param.icon, that.param.duration);
    if(ret){
        WEBVIEWCORE.trigger( 'failed', that.handlerId, 1003, ret);
        return;
    }

    // 确认事件
    component.accepted.connect(function() {
      // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
      WEBVIEWCORE.trigger('success',that.handlerId);
      SYBEROS.destroy(that.id);
    });
  });
}

Toast.prototype = SyberPlugin.prototype
