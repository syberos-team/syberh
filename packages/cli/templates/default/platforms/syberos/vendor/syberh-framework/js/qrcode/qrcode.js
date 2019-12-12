/* eslint-disable no-undef */

/***
 * image.qrcode(Object object)
 */
function Qrcode () {
  var defaultOpts = {
    id: 'qrcode',
    module: 'qrcode',
    page: true,
    methods: ['scan'],
    source: '../qml/SQrcode.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this
  this.on('scan', function (object, handlerId, param) {
    var component = object || that.object

    console.log('*******scan*******scan*******scan********scan***')

      component.decodeFinished.connect(function (decodeContent) {
          console.log('qrcode.scan.ok*****************************', decodeContent)
          pageStack.pop(currentWebview.object);
          that.success(that.handlerId, { result: decodeContent });
          SYBEROS.destroy(that.id);
      })

      component.cancel.connect(function () {
          console.log('qrcode.scan.cancel*****************************')
          pageStack.pop(currentWebview.object);
          that.success(that.handlerId);
          SYBEROS.destroy(that.id);
      })
  })
}

Qrcode.prototype = SyberPlugin.prototype
