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
    component.titleText = that.param.title
    component.messageText = that.param.message
    component.acceptButtonLoading = that.param.showLoading
    component.rejectButtonVisible = that.param.showCancel
    component.rejectButtonText = that.param.cancelText
    component.rejectButtonColor = that.param.cancelColor
    component.acceptedButtonText = that.param.confirmText
    component.acceptButtonColor = that.param.confirmColor

    component.show()


    component.accepted.connect(function () {
      console.log('-----prompt accepted')
    })
  })

}

Prompt.prototype = SyberPlugin.prototype
