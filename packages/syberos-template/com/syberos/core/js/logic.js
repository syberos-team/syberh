Qt.include('polyfill.js')
Qt.include('webview.js')
//增加对ES6语法的支持
polyfill()



//根目录节点
var _root = null
var _helper = null

var webviews = []

var webView = null

function init(parent) {
  if (!root && !parent) {
    throw new Error('root节点不存在或者未进行初始化')
  }
  _root = root || parent
}

/**
 *  创建body节点
 * @param {function} callback 返回父节点
 *
 */
function bodyElement(callback) {
  var component = Qt.createComponent('../qml/boby.qml')
  var boby = component.incubateObject(_root)

  if (boby.status !== Component.Ready) {
    boby.onStatusChanged = function(status) {
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

function render(root) {
  if (root) {
    _root = root
  }
  //先创建body节点，再创建其他
  bodyElement(function(parent) {
    if (!webView) {
      webView = new WebView(parent)
    }
    webView.init()
  })

  //var url = getIndexPath()
  //initNativeSdkManager()

  // initWebView(_root, url)

  // initWebView(_root, url)

  //  var component = Qt.createComponent('../qml/webview.qml')
  //  var that = this
  //  print('\n #############----------------------')
  //  print('widht', root.width)
  //  print('height', root.height)
  //  var incubator = component.incubateObject(root, {
  //    width: 400,
  //    height: 500,
  //    x: 10,
  //    y: 10
  //  })

  //    if (incubator.status !== Component.Ready) {
  //        incubator.onStatusChanged = function(status) {
  //            print("----",incubator.url)
  //            console.log('\n------incubator.status',incubator.status,Component.Ready)
  //            if (status === Component.Ready) {

  //                //incubator.url="https://baidu.com";
  //                print ("\n Object", incubator.object, "is now ready!");
  //            }
  //        }
  //    } else {
  //        print ("\n Object", incubator.object, "is ready immediately!");
  //    }
}

//function reload() {
//  webviews[0].url = 'https://baidu.com'
//}

//function hidden() {
//  webviews[0].visible = false
//}

//function destroy() {
//  webviews[0].destroy(1000)
//}

//var component
//function initWebView(root, url, callback) {
//  component = Qt.createComponent('../qml/webview.qml')

//  if (
//    component.status === Component.Ready ||
//    component.status === Component.Error
//  ) {
//    //component.url=url;
//    console.log(',,,component.status ,,,', component.status)
//    console.log(',,,,,,', JSON.stringify(component))
//    finishCreation()
//  } else {
//    component.statusChange.connect(finishCreation)
//  }
//}

//function resetXY() {
//  var x = 0
//  var y = 0
//  for (var i = 0; i < webviews.length; i++) {
//    var v = webviews[i]
//    v.x = x
//    v.y = y
//    y += 250
//  }
//}

//function finishCreation(x, y) {
//  console.log('----webViewChange-', component.status)
//  if (component.status === Component.Ready) {
//    var webview = component.createObject(_root, {
//      width: 300,
//      height: 200
//    })
//    if (webview === null) {
//      console.log('Error creating image')
//    } else {
//      webviews.push(webview)
//      webview.receiveMessage.connect(onMessageReceived)
//      console.log(webview.receiveMessage)
//      for (var i in NativeSdkManager) {
//        console.log('>>>>>', i, NativeSdkManager[i])
//      }

//      webview.url = getIndexPath()
//      //webview.onMeesage=onMessageReceived
//    }
//  } else if (component.status === Component.Error) {
//    console.log('Error loading component:', component.errorString())
//  }
//}

//function initNativeSdkManager() {
//  NativeSdkManager.sucess.connect(success)

//  NativeSdkManager.failed.connect(failed)
//}

//function success(responseID, result) {
//  console.log('request sucess ', result)
//  console.log('responseID ', responseID)
//  gToast.requestToast('request sucess ' + result)
//}

//function failed(responseID, errorCode, errorMsg) {
//  console.log('request failed ' + errorMsg)
//  var callbackId = responseID
//  var obj = {
//    responseId: callbackId,
//    responseData: {
//      code: 0,
//      msg: errorMsg
//    }
//  }
//  webviews[0].experimental.evaluateJavaScript(
//    'JSBridge._handleMessageFromNative(' + JSON.stringify(obj) + ')'
//  )
//}

function getIndexPath() {
  var url = 'file://' + helper.getWebRootPath() + '/index.html'

  console.log('\n url', url, '\n')
  return url
}
