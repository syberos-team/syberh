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
    source: '../qml/sprompt.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this

  this.on('prompt', function (object) {

    console.log('\n')
    console.log('prompt ready', object)
    console.log('\n')
    var component = object || that.object
    component.titleText = that.param.title || ''
    component.icon = that.param.titleIcon || ''
    component.messageText = that.param.content || ''
    component.acceptButtonLoading = that.param.showLoading  || false
    component.rejectButtonVisible = that.param.showCancel  || false
    component.rejectButtonText = that.param.cancelText || '取消'
    component.rejectButtonColor = that.param.cancelColor || '#333333'
    component.acceptedButtonText = that.param.confirmText || '确定'
    component.acceptButtonColor = that.param.confirmColor || '#007aff'

    component.show()


    component.accepted.connect(function (value) {
      that.clearParam()
      WEBVIEWCORE.trigger('success', that.handlerId, { confirm: true, data: value })
    })

    component.rejected.connect(function () {
      that.clearParam()
      WEBVIEWCORE.trigger('success', that.handlerId, { cancel: true })
    })

  })

}

Prompt.prototype = SyberPlugin.prototype
