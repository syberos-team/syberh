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

  // 是否第一次绑定接受信号
  this.firstConnect = false

  var that = this
  this.on('gtoast',function(){
    if(!that.param.title){
        WEBVIEWCORE.trigger( 'failed', that.handlerId, { "code": 0, "msg": "提示的内容不能为空"});
        return;
    }
    gToast.requestToast(that.param.title)
  });

  this.on('toast', function (object, handlerId, param) {
    var component = object || that.object

    if(!that.param.title){
        WEBVIEWCORE.trigger( 'failed', that.handlerId, { "code": 0, "msg": "提示的内容不能为空"});
        return;
    }

    component.hide();

    if(!that.param.icon){
        that.param.icon = "success";
    }
    component.icon = that.param.icon;

    var strlength = getStrLength(that.param.title);
    if(that.param.icon !== "none" && strlength > 14){
        WEBVIEWCORE.trigger( 'failed', that.handlerId, { "code": 0, "msg": "有图标时最多7个汉字长度的文本"});
        return;
    }
    if(that.param.icon === "none" && strlength > 28 ){
        WEBVIEWCORE.trigger('failed',that.handlerId,{ "code": 0, "msg": "无图标时最多显示两行文本（14个汉字长度）"});
        component.hide();
        return;
    }

    component.title = that.param.title;
    if(that.param.duration){
        component.duration = that.param.duration;
    }

    component.show();

    // 只做一次信号绑定,防止多次信号被触发
    if(!that.firstConnect) {
      // 设置绑定信号
      that.firstConnect = true

      // 成功事件
      component.accepted.connect(function() {
        // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
        WEBVIEWCORE.trigger('success',that.handlerId)
      })
    }

  });
}

Toast.prototype = SyberPlugin.prototype
