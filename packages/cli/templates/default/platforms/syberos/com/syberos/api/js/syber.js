Qt.include('util/polyfill.js')
Qt.include('util/tool.js')
Qt.include('util/log.js')
Qt.include('config.js')
Qt.include('core/core.js')
Qt.include('core/plugin.js')
Qt.include('root/root.js')
Qt.include('webview/webview.js')
Qt.include('modal/alert.js')
Qt.include('modal/confirm.js')
Qt.include('modal/prompt.js')
Qt.include('modal/toast.js')
Qt.include('modal/gtoast.js')
Qt.include('camera/capture.js')
Qt.include('system/system.js')
Qt.include('filepicker/filepicker.js')
Qt.include('image/choose.js')
Qt.include('image/chooseImage.js')
Qt.include('image/previewImage.js')
// 增加对ES6语法的支持
polyfill()

// 根目录节点
var _root = null
var _spage = null

/**
 * 初始化syberh core
 * @param {object} root 渲染的根节点 
 * @param {object} spage page
 */
function init (root, spage) {
  if (!root) {
    logger.error("init() ,渲染节点错误错误")
    throw new Error("渲染节点错误错误")
  }
  if (!spage) {
    logger.error("init() ,当前默认webview节点错误")
    throw new Error("当前默认webview节点错误")
  }

  _root = root
  _spage = spage
  if (!SYBEROS) {
    var SyberOS = new Syber(root)
    SYBEROS = SyberOS
  }
}
