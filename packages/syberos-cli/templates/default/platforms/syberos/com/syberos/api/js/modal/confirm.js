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

  // 是否第一次绑定接受信号
  this.firstConnect = false

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

    component.show()


    // 只做一次信号绑定,防止多次信号被触发
    if(!that.firstConnect) {
        // 设置绑定信号
        that.firstConnect = true

        // 确认事件
        component.accepted.connect(function() {
            // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
            WEBVIEWCORE.trigger('success', that.handlerId, true)
            // 清理相关参数信息
            that.clearParam()
        })

        // 确认事件
        component.rejected.connect(function() {
            // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
            WEBVIEWCORE.trigger('success', that.handlerId, false)
            // 清理相关参数信息
            that.clearParam()
        })
    }

  })

}

Confirm.prototype = SyberPlugin.prototype
