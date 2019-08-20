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

    // 确认事件
    component.accepted.connect(function () {
      that.clearParam()
      WEBVIEWCORE.trigger('success', that.handlerId)
    })

  })
}

Alert.prototype = SyberPlugin.prototype
