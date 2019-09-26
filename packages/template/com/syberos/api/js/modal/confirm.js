/* eslint-disable no-undef */

/***
 * modal.confirm(Object)
 */
function Confirm () {
  var defaultOpts = {
    id: 'confirm',
    name: 'confirm',
    module: 'modal',
    methods: ['confirm'],
    source: '../qml/SConfirm.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this

  this.on('confirm', function (object) {

    console.log('\n')
    console.log('confirm ready', JSON.stringify(that.param))
    console.log('\n')
    var component = object || that.object

    component.titleText = that.param.title || ''
    component.icon = that.param.titleIcon||""
    component.messageText = that.param.content || ''
    component.rejectButtonText = that.param.cancelText || '取消'
    component.rejectButtonColor = that.param.cancelColor || '#333333'
    component.acceptedButtonText = that.param.confirmText || '确定'
    component.acceptButtonColor = that.param.confirmColor || '#007aff'


    if(that.param.title && that.param.title.length > 7){
        that.failed(that.handlerId, 1003, "标题最多7个汉字");
        return;
    }

    if(that.param.confirmText && that.param.confirmText.length > 4 || that.param.cancelText && that.param.cancelText.length > 4){
        that.failed(that.handlerId, 1003, "按钮最多4个汉字");
        return;
    }

    component.show()


    // 确认事件
    component.accepted.connect(function() {
        // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
        that.success(that.handlerId, true);
        // 清理相关参数信息
        that.clearParam()
    })

    // 确认事件
    component.rejected.connect(function() {
        // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
        that.success(that.handlerId, false);
        // 清理相关参数信息
        that.clearParam()
    })


  })

}

Confirm.prototype = SyberPlugin.prototype
