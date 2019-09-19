/* eslint-disable no-undef */

/***
 * modal.select()
 */
function Select () {
  var defaultOpts = {
    id: 'select',
    name: 'select',
    module: 'image',
    methods: ['select'],
    source: '../qml/SImageSelector.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  // 是否第一次绑定接受信号
  this.firstConnect = false

  var that = this
  this.on('select', function (object, handlerId, param) {
    var component = object || that.object

    console.log('\n')
    console.log('alert request', component.z)
    console.log('paramparamparamparamparam', JSON.stringify(param))

    component.count = param.count
    component.open(param)

    // 只做一次信号绑定,防止多次信号被触发
    if(!that.firstConnect) {
      // 设置绑定信号
      that.firstConnect = true

      // 确认事件receiveMessage
      component.receiveUrls.connect(function(arr) {
          console.log('image select receive---', arr)
          // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
          WEBVIEWCORE.trigger('success',that.handlerId, arr)
          // 清理相关参数信息
          that.clearParam()
      })
    }

  })
}

Select.prototype = SyberPlugin.prototype
