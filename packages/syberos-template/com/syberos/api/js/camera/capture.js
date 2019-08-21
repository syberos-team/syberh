/* eslint-disable no-undef */

/***
 * capture.alert(Object)
 */
function Capture () {
  var defaultOpts = {
    id: 'capture',
    name: 'capture',
    module: 'camera',
    page: true,
    methods: ['takePictureImmediately'],
    source: '../qml/SCamera.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  // 开关
  this.imageConfirmedFlag = false

  var that = this
  this.on('takePictureImmediately', function (object) {

//    console.log('-------------------------------------object', object)
//    object.back.connect(function (path) {
//        console.log('-------------------------------------message',path)
//        pageStack.pop()
//        WEBVIEWCORE.trigger('success', that.handlerId, { path: path })
//    })

    if (!that.imageConfirmedFlag) {
        object.imageConfirmed.connect(function(filePath) { //处理信号
            console.log('-------------------------------------filePath----js', filePath)
            that.imageConfirmedFlag = true
            pageStack.pop(root)
            filePath = "file://"+filePath;
            WEBVIEWCORE.trigger('success', that.handlerId, { path: filePath })
        })
    }

  })

  this.on('ready', function () {
    console.log('\n')
    console.log('Capture ready')
  })
}

Capture.prototype = SyberPlugin.prototype
