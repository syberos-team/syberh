/* eslint-disable no-undef */

/***
 * modal.alert(Object)
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
    var component = object || that.object

    if(!that.param.title){
        WEBVIEWCORE.trigger( 'failed', that.handlerId, { "code": 0, "msg": "提示的内容不能为空"});
        return;
    }

    component.hide();

    if(!that.param.icon){
        console.log("that.param.icon : "+ that.param.icon);
        that.param.icon = "success";
    }
    component.icon = that.param.icon;

    var strlength = getStrLength(that.param.title);
    if(that.param.icon !== "none" && strlength > 14){
        console.log("1414141414");
        WEBVIEWCORE.trigger( 'failed', that.handlerId, { "code": 0, "msg": "有图标时最多7个汉字长度的文本"});
        return;
    }
    console.log("that.param: "+ JSON.stringify(that.param));
    console.log("strlength: "+ strlength);
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
  });
}

function getStrLength(inputStr){
    var currLength = 0;
    if(!inputStr){
        return currLength;
    }

    for(var i = 0; i < inputStr.length; i++){
        var item = inputStr.charAt(i);
        //中文字符的长度经编码之后大于4
        if(escape(item).length > 4){
            currLength += 2;
        }else{
            currLength += 1;
        }
    }
    return currLength;
}

Toast.prototype = SyberPlugin.prototype
