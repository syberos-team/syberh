Qt.include('polyfill.js')
Qt.include('tool.js')
Qt.include('lib/core.js')
Qt.include('lib/plugin.js')
Qt.include('root/root.js')
Qt.include('webview/webview.js')
Qt.include('config.js')

// 增加对ES6语法的支持
polyfill()

// 根目录节点
var _root = null
var _helper = null

var webviews = []

var webView = null

/**
 *  创建body节点
 * @param {function} callback 返回父节点
 *
 */
function bodyElement (callback) {
  var component = Qt.createComponent('../qml/boby.qml')
  var boby = component.incubateObject(_root)

  if (boby.status !== Component.Ready) {
    boby.onStatusChanged = function (status) {
      if (status === Component.Ready) {
        boby.object.height = _root.height
        boby.object.width = _root.width
        console.log('-----z', boby.object.z)
        if (typeof callback === 'function') {
          callback(boby.object)
        }
      }
    }
  }
}

function render (root) {
  if (root) {
    _root = root
  }
  // 先创建body节点，再创建其他
//  bodyElement(function (parent) {
//    if (!webView) {
//      webView = new WebView(parent)
//    }
//  })

  var SyberOS = new Syber()


  //SyberOS.addPlugin(RootItem)
}
