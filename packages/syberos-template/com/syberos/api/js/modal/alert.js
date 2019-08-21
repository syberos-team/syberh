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

  // 是否第一次绑定接受信号
  this.firstConnect = false

  var that = this
  this.on('alert', function (object, handlerId, param) {
    var component = object || that.object

    console.log('\n')
    console.log('alert request', component.z)
    console.log('\n', param)


    component.rejectButtonVisible = false

    component.titleText = that.param.title || ''
    component.icon = that.param.titleIcon|| ''
    component.messageText = that.param.content || ''
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
          WEBVIEWCORE.trigger('success',that.handlerId)
          // 清理相关参数信息
          that.clearParam()
      })
    }

  })
}

Alert.prototype = SyberPlugin.prototype
