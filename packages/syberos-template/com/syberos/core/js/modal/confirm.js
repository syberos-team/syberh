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
    component.titleText =  that.param.title || ''
    component.messageText = that.param.message
    component.acceptButtonLoading = that.param.showLoading ? true : false
    component.icon = that.param.titleIcon||""

    component.show()
    component.accepted.connect(function () {
        component.titleText = ''
        WEBVIEWCORE.trigger('success', that.handlerId, { confirm: true })
      console.log('-----confirm accepted')
    })
  })

}

Confirm.prototype = SyberPlugin.prototype
