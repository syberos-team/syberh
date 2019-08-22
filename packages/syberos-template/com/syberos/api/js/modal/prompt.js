/* eslint-disable no-undef */

/***
 * modal.prompt(Object)
 */
function Prompt () {
  var defaultOpts = {
    id: 'prompt',
    name: 'prompt',
    module: 'modal',
    methods: ['prompt'],
    autoCreate: true, // lineEdit loader加载不出来， 设置自动加载一次
    source: '../qml/SInputDialog.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  // 是否第一次绑定接受信号
  this.firstConnect = false

  var that = this

  that.on('prompt', function (object) {

    console.log('\n')
    console.log('prompt ready', object)
    console.log('\n')
    var component = object || that.object
    component.titleText = that.param.title || ''
    component.rejectButtonText = that.param.cancelText || '取消'
    component.acceptedButtonText = that.param.confirmText || '确定'

    component.show()

    // 只做一次信号绑定,防止多次信号被触发
    if(!that.firstConnect) {
        // 设置绑定信号
      that.firstConnect = true

      // 确认事件
      component.inputAccepted.connect(function(value) {
          console.log(value)
          // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
          WEBVIEWCORE.trigger('success', that.handlerId, value)
          // 清理相关参数信息
          that.clearParam()
      })
    }

  })

}

Prompt.prototype = SyberPlugin.prototype
