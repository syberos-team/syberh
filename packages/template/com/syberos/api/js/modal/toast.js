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
        WEBVIEWCORE.trigger( 'failed', that.handlerId, 0, "提示的内容不能为空");
        return;
    }
    gToast.requestToast(that.param.title);
    WEBVIEWCORE.trigger('success',that.handlerId);
  });

  this.on('toast', function (object, handlerId, param) {
    var component = object || that.object

    if(!that.param.title){
        WEBVIEWCORE.trigger( 'failed', that.handlerId, 0, "提示的内容不能为空");
        return;
    }

    component.hide();

    if(!that.param.icon){
        that.param.icon = "success";
    }
    component.icon = that.param.icon;

    var strlength = getStrLength(that.param.title);
    if(that.param.icon !== "none" && strlength > 14){
        WEBVIEWCORE.trigger( 'failed', that.handlerId, 0, "有图标时最多7个汉字长度的文本");
        return;
    }
    if(that.param.icon === "none" && strlength > 28 ){
        WEBVIEWCORE.trigger('failed',that.handlerId, 0, "无图标时最多显示两行文本（14个汉字长度）");
        component.hide();
        return;
    }

    component.title = that.param.title;
    if(that.param.duration){
        component.duration = that.param.duration;
    }

    component.show();

    WEBVIEWCORE.trigger('success',that.handlerId);

  });
}

Toast.prototype = SyberPlugin.prototype
