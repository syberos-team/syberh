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

    // 只做一次信号绑定,防止多次信号被触发
    if(!that.firstConnect) {
      // 设置绑定信号
      that.firstConnect = true

      // 确认事件 receiveUrls
      component.receiveUrls.connect(function(result) {
          console.log('chooseImage 返回值是---', result)
          // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
          WEBVIEWCORE.trigger('success',that.handlerId, result)
          // 清理相关参数信息
          that.clearParam()
      })
    }

  })
}

ChooseImage.prototype = SyberPlugin.prototype
