/* eslint-disable no-undef */

/***
 * modal.alert(Object)
 */
function Alert () {
  var defaultOpts = {
    id: 'alert',
    name: 'alert',
    module: 'modal',
    methods: ['alert'],
    source: '../qml/SConfirm.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this
  this.on('alert', function (object, handlerId, param) {
    var component = object || that.object

    console.log('modal alert', JSON.stringify(that.param))

    component.rejectButtonVisible = false

    component.titleText = that.param.title || ''
    component.icon = that.param.titleIcon|| ''
    component.messageText = that.param.content || ''
    component.acceptedButtonText = that.param.confirmText || '确定'
    component.acceptButtonColor = that.param.confirmColor || '#007aff'

    if (!that.param.content) {
        that.failed(that.handlerId, 9001, "content不能为空");
        return;
    }

    if(that.param.title && that.param.title.length > 7){
        that.failed(that.handlerId, 9001, "标题最多7个汉字");
        return;
    }

    if(that.param.confirmText && that.param.confirmText.length > 4){
        that.failed(that.handlerId, 9001, "按钮最多4个汉字");
        return;
    }

    component.show()


    // 确认事件
    component.accepted.connect(function() {
      // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
      that.success(that.handlerId);
      // 清理相关参数信息
      that.clearParam()
    })

  })
}

Alert.prototype = SyberPlugin.prototype
