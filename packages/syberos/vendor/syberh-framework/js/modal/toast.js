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
       that.failed(that.handlerId, 9002, "组件初始化错误");
    }
    var ret = component.show(that.param.title, that.param.icon, that.param.duration);
    if(ret){
        logger.verbose('component.show ret:',ret)
        that.failed(that.handlerId, 9001, ret);
        return;
    }else{
       that.success(that.handlerId);
    }
  });
}

Toast.prototype = SyberPlugin.prototype
