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
    source: '../qml/alert.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this
  this.on('alert', function (object, handlerId, param) {
    var component = object || that.object

    console.log('\n')
    console.log('alert request', component.z)
    console.log('\n', param)
    component.show()

    // 确认事件
    component.accepted.connect(function () {
      WEBVIEWCORE.trigger('success', that.handlerId, { confirm: true })
      console.log('-----alert accepted')
    })
    // 取消确认事件
    component.accepted.connect(function () {
      // 取消

      WEBVIEWCORE.trigger('success', that.handlerId, { cancel: true })
      console.log('-----alert accepted')
    })
  })
}

Alert.prototype = SyberPlugin.prototype
