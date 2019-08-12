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
    source: '../qml/SAlert.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this
  this.on('alert', function (object, handlerId, param) {
    var component = object || that.object

    console.log('\n')
    console.log('alert request', component.z)
    console.log('\n', param)
    component.titleText = that.param.title
    component.messageText = that.param.message
    component.rejectButtonVisible = that.param.showCancel
    component.show()

//    // 确认事件
    component.accepted.connect(function () {
      WEBVIEWCORE.trigger('success', that.handlerId, { confirm: true })
      console.log('-----alert accepted')
    })

  })
}

Alert.prototype = SyberPlugin.prototype
