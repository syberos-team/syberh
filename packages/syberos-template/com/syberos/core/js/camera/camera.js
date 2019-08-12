/* eslint-disable no-undef */

/***
 * camera.alert(Object)
 */
function Camera () {
  var defaultOpts = {
    id: 'camera',
    name: 'camera',
    module: 'camera',
    page: true,
    methods: ['takePictureImmediately'],
    source: '../qml/camera.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this
  this.on('takePictureImmediately', function (object, handlerId, param) {
    var component = object || that.object

    console.log('\n')
    console.log('alert request')
    console.log('\n', param)
    // component.show()
  })

  this.on('ready', function () {
    console.log('\n')
    console.log('Camera ready')
  })
}

Camera.prototype = SyberPlugin.prototype
