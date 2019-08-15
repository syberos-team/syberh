/* eslint-disable no-undef */

/***
 * barcode.scan(Object)
 */
function Barcode () {
  var defaultOpts = {
    id: 'barcode-scan',
    module: 'barcode',
    page: true,
    methods: ['scan'],
    source: '../qml/SBarcode.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this
  this.on('scan', function (object, handlerId, param) {
    var component = object || that.object

    console.log('\n')
    console.log('###### barcode.qrcode request')
    console.log('\n', param)

    object.back.connect(function (cotent) {
      console.log('-------------------------------------barcode scan content', cotent)
      WEBVIEWCORE.trigger('success', that.handlerId, { cotent: cotent })
    })
  })

  this.on('ready', function () {
    console.log('\n')
    console.log('###### barcode ready')
  })
}

Barcode.prototype = SyberPlugin.prototype
