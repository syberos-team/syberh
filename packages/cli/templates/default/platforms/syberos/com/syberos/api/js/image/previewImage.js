/* eslint-disable no-undef */

/***
 * image.previewImage(Object object)
 */
function PreviewImage () {
  var defaultOpts = {
    id: 'previewImage',
    module: 'image',
    page: true,
    methods: ['previewImage'],
    source: '../qml/SPreviewImage.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this

  this.on('previewImage', function (object, handlerId, param) {
    var component = object || that.object
    logger.verbose('image.previewImage() 接受到的参数: [ %s ]', JSON.stringify(that.param))

    if (!Array.isArray(that.param.urls)) {
        WEBVIEWCORE.trigger('failed', that.handlerId, 1003, "urls必须是数组格式");
    } else if (Array.isArray(that.param.urls) && that.param.urls === 0) {
        WEBVIEWCORE.trigger('failed', that.handlerId, 1003, "urls不能是空数组");
    }

    component.showPage(param)

    // 确认事件
    component.success.connect(function () {
        logger.verbose('image.previewImage() 接受到成功信号')
        // 此处必须用that.xx ，因为后续的参数不会被传到该方法范围内
        WEBVIEWCORE.trigger('success',that.handlerId)
        // 注销qml组件
        SYBEROS.destroy(defaultOpts.id)
    })
  })
}


PreviewImage.prototype = SyberPlugin.prototype
