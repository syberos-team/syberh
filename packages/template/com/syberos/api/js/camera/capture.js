/* eslint-disable no-undef */

/***
 * capture.alert(Object)
 */
function Capture () {
  var defaultOpts = {
    id: 'camera',
    module: 'camera',
    page: true,
    methods: ['takePhoto'],
    source: '../qml/SCamera.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this
  this.on('takePhoto', function (object) {

//    object.back.connect(function (path) {
//        pageStack.pop()
//        WEBVIEWCORE.trigger('success', that.handlerId, { path: path })
//    })

    object.imageConfirmed.connect(function(filePath) { //处理信号
        that.imageConfirmedFlag = true
        pageStack.pop(currentWebview.object)
        WEBVIEWCORE.trigger('success', that.handlerId, { path: filePath })
        SYBEROS.destroy(that.id)
    })

  })

}

Capture.prototype = SyberPlugin.prototype
