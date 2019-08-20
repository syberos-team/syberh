/* eslint-disable no-undef */
/* eslint-disable no-unused-vars */
Qt.include('util/polyfill.js')
Qt.include('util/tool.js')
Qt.include('config.js')
Qt.include('core/core.js')
Qt.include('core/plugin.js')
Qt.include('root/root.js')
Qt.include('webview/webview.js')
Qt.include('modal/alert.js')
Qt.include('modal/confirm.js')
Qt.include('modal/prompt.js')
Qt.include('modal/toast.js')
Qt.include('camera/camera.js')
// 增加对ES6语法的支持
polyfill()

// 根目录节点
var _root = null
var _helper = null

var webviews = []

var webView = null

function render (root) {
  if (root) {
    _root = root
  }
  if(!SYBEROS){
      var SyberOS = new Syber(root)
      SYBEROS = SyberOS
  }

  //SyberOS.addPlugin(new Camera())
}
