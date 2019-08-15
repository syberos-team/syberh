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
  this.on('takePictureImmediately', function (object) {

    console.log('-------------------------------------object', object)
    object.back.connect(function (path) {
        console.log('-------------------------------------message',path)
        pageStack.pop()
        WEBVIEWCORE.trigger('success', that.handlerId, { path: path })
    })
  })

  this.on('ready', function () {
    console.log('\n')
    console.log('Camera ready')
  })
}

Camera.prototype = SyberPlugin.prototype
