/* eslint-disable no-undef */

/***
 * modal.alert(Object)
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


  // 是否第一次绑定接受信号
  this.firstConnectToast = false;

  this.on('toast', function (object, handlerId, param) {
    var component = object || that.object

//    if(!that.param.title){
//        WEBVIEWCORE.trigger( 'failed', that.handlerId, 1003, "提示的内容不能为空");
//        return;
//    }

    //component.hide();


    var ret = component.show(that.param.title, that.param.icon, that.param.duration);
    if(ret){
        WEBVIEWCORE.trigger( 'failed', that.handlerId, 1003, ret);
        return;
    }

    // 只做一次信号绑定,防止多次信号被触发
    if(!that.firstConnectToast) {
      // 设置绑定信号
      that.firstConnectToast = true

      // 确认事件
      component.accepted.connect(function() {
          // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
          WEBVIEWCORE.trigger('success',that.handlerId);
          SYBEROS.destroy(defaultOpts.id);
      });
    }
  });
}

Toast.prototype = SyberPlugin.prototype
