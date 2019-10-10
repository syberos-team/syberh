/* eslint-disable no-undef */

/***
 * image.chooseImage(Object object)
 */
function ChooseImage () {
  var defaultOpts = {
    id: 'chooseImage',
    name: 'chooseImage',
    module: 'image',
    methods: ['chooseImage'],
    source: '../qml/SChooseImage.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  // 是否第一次绑定接受信号
  this.firstConnect = false

  var that = this
  this.on('chooseImage', function (object, handlerId, param) {
    var component = object || that.object

    component.open(param)

      // 确认事件
      component.receiveUrls.connect(function(result) {
          console.log('chooseImage 返回值是---', result)
          // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
          WEBVIEWCORE.trigger('success',that.handlerId, result)
          SYBEROS.destroy(that.id)
      })


      // 相机拍完一张的事件
      component.cameraSuccess.connect(function(result) {
          pageStack.pop(currentWebview.object)
          WEBVIEWCORE.trigger('success', that.handlerId, result)
          SYBEROS.destroy(that.id)
      })

      // 相机取消
      component.cameraCancel.connect(function() {
          pageStack.pop(currentWebview.object)
          SYBEROS.destroy(that.id)
      })

      // 相册取消
      component.albumCancel.connect(function() {
          console.log('albumCancel--')
          SYBEROS.destroy(that.id)
      })

  })
}

ChooseImage.prototype = SyberPlugin.prototype
