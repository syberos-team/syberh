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

  var that = this
  this.on('chooseImage', function (object, handlerId, param) {
    var component = object || that.object

    component.open(param)

      // 取消事件
      component.cancel.connect(function() {
          console.log('chooseImage cancel---')
          // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
          WEBVIEWCORE.trigger('success',that.handlerId)
          SYBEROS.destroy(that.id)
      })

      // 确认事件
      component.receiveUrls.connect(function(result) {
          console.log('chooseImage 返回值是---', JSON.stringify(result), that.handlerId)
          // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
          WEBVIEWCORE.trigger('success',that.handlerId, result)
          SYBEROS.destroy(that.id)
      })


      // 相机拍完一张的事件
      component.cameraSuccess.connect(function(result) {
          console.log('chooseImage cameraSuccess--', JSON.stringify(result))
          pageStack.pop(currentWebview.object)
          WEBVIEWCORE.trigger('success', that.handlerId, result)
          SYBEROS.destroy(that.id)
      })

      // 相机取消
      component.cameraCancel.connect(function() {
          console.log('chooseImage cameraCancel--')
          pageStack.pop(currentWebview.object)
          SYBEROS.destroy(that.id)
      })

      // 相册取消
      component.albumCancel.connect(function() {
          console.log('chooseImage albumCancel--')
          SYBEROS.destroy(that.id)
      })

  })
}

ChooseImage.prototype = SyberPlugin.prototype
