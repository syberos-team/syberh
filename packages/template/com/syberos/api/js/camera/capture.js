/* eslint-disable no-undef */

/***
 * capture.takePictureImmediately(Object)
 */
function Capture () {
  var defaultOpts = {
    id: 'camera',
    module: 'camera',
    page: true,
    methods: ['takePictureImmediately'],
    source: '../qml/SCamera.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this
  this.on('takePictureImmediately', function (object) {

//    console.log('-------------------------------------object', object)
//    object.back.connect(function (path) {
//        console.log('-------------------------------------message',path)
//        pageStack.pop()
//        WEBVIEWCORE.trigger('success', that.handlerId, { path: path })
//    })

    object.imageConfirmed.connect(function(filePath) { //处理信号
        that.imageConfirmedFlag = true
        pageStack.pop(currentWebview.object);
        filePath = "file://"+filePath;
        WEBVIEWCORE.trigger('success', that.handlerId, { path: filePath });
        SYBEROS.destroy(defaultOpts.id);
    })


  })

}

Capture.prototype = SyberPlugin.prototype
