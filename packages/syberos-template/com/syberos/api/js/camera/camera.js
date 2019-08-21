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
    source: '../qml/SCamera.qml'
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

//    object.imageConfirmed.connect(function(filePath) { //处理信号
//        console.log('-------------------------------------filePath----js', filePath)
//        pageStack.pop(root)

//        WEBVIEWCORE.trigger('success', that.handlerId, { path: filePath })
//    })


  })

  this.on('ready', function () {
    console.log('\n')
    console.log('Camera ready')
  })
}

Camera.prototype = SyberPlugin.prototype
