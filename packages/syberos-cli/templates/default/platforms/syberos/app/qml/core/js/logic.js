//.pragma library

// import { initWebView } from './webview.mjs'
//根目录节点
var _root = null
var component

function render(parent) {
  if (!r) {
    throw new Error('root不能为空')
  }
  _root = parent

  //initWebView(root)

  component = Qt.createComponent('../qml/dynamic-image.qml')
  if (
    component.status === Component.Ready ||
    component.status === Component.Error
  ) {
    finishCreation()
  } else {
    component.statusChanged.connect(finishCreation)
  }
}

function finishCreation() {
  if (component.status === Component.Ready) {
    var image = component.createObject(root, { x: 100, y: 100 })
    if (image === null) {
      console.log('Error creating image')
    }
  } else if (component.status === Component.Error) {
    console.log('Error loading component:', component.errorString())
  }
}
