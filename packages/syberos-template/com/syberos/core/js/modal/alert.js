/* eslint-disable no-undef */

/***
 * modal.alert(Object)
 */
function Alert () {
  var defaultOpts = {
    id: 'alert',
    name: 'alert',
    module: 'modal',
    source: '../qml/alert.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this

  this.onReady = function (object) {
    console.log('\n')
    console.log('alert ready', object.z)
    console.log('\n')
    var component = object || that.object
    component.show()

    component.accepted.connect(function () {
      console.log('-----alert accepted')
    })
  }
}

Alert.prototype = SyberPlugin.prototype
