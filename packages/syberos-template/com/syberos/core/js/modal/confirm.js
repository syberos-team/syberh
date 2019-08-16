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
    component.acceptButtonLoading = that.param.showLoading  || false
    component.rejectButtonVisible = that.param.showCancel  || false
    component.rejectButtonText = that.param.cancelText || '取消'
    component.rejectButtonColor = that.param.cancelColor || '#333333'
    component.acceptedButtonText = that.param.confirmText || '确定'
    component.acceptButtonColor = that.param.confirmColor || '#007aff'

    component.show()

    component.accepted.connect(function () {
        that.clearParam()
        WEBVIEWCORE.trigger('success', that.handlerId, { confirm: true })
    })

    component.rejected.connect(function () {
        that.clearParam()
        WEBVIEWCORE.trigger('success', that.handlerId, { cancel: true })
    })
  })

}

Confirm.prototype = SyberPlugin.prototype
