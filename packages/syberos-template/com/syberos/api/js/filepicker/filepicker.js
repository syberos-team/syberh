/* eslint-disable no-undef */

/***
 * modal.alert(Object)
 */
function FilePicker () {
  var defaultOpts = {
    id: 'filepicker',
    module: 'filepicker',
    page: true,
    methods: ['open'],
    source: '../qml/SFilesPicker.qml'
  }
  SyberPlugin.call(this, defaultOpts)


  var that = this

    this.on('open', function (object, handlerId, param) {
        var component = object || that.object

        component.titleText = that.param.title || ""
        component.leftItemEnabled = that.param.showBack || false


        component.ok.connect(function(filePath) { //处理选择文件信号
            console.log('----filePath---', filePath)
            filePath = "file://"+filePath;
            WEBVIEWCORE.trigger('success', that.handlerId, { confirm:true, path: filePath })
        })

        component.cancel.connect(function() { //处理取消信号
            console.log('----cancel---')
            WEBVIEWCORE.trigger('success', that.handlerId, { cancel: true })
        })

    })
}

FilePicker.prototype = SyberPlugin.prototype
