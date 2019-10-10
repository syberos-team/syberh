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
      var component = object || that.object

//    component.back.connect(function (path) {
//        pageStack.pop(currentWebview.object)
//        WEBVIEWCORE.trigger('success', that.handlerId, { path: path })
//        SYBEROS.destroy(that.id)
//    })

    component.imageConfirmed.connect(function(filePath) {
        that.imageConfirmedFlag = true;
        pageStack.pop(currentWebview.object);
        WEBVIEWCORE.trigger('success', that.handlerId, { path: filePath });
        SYBEROS.destroy(that.id);
    });

    component.imageCancele.connect(function() {
        pageStack.pop(currentWebview.object);
        WEBVIEWCORE.trigger('success',that.handlerId);
        SYBEROS.destroy(that.id);
    });

  })

}

Capture.prototype = SyberPlugin.prototype
