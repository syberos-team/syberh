# QML 插件开发

##新增一个插件

方式一

```
 var defaultOpts = {
    id: 'alert',
    name: 'alert',
    module: 'modal',
    source: '../qml/alert.qml'
  }
var alert=new SyberPlugin(defaultOpts)

#添加到组件
SyberOS.addPlugin(alert);

#此方法创建一个新的组件

```

方式二

```

function Alert(opts){
   var defaultOpts = {
    id: 'alert',
    name: 'alert',
    module: 'modal',
    source: '../qml/alert.qml'
  }
 SyberPlugin.call(this, defaultOpts)
}

Alert.prototype = SyberPlugin.prototype

#添加到组件
SyberOS.addPlugin(new Alert());



```

##插件返回

统一通过 webview 的 success/failed 事件进行返回

```
WEBVIEWCORE.trigger('success', that.handlerId, { confirm: true })
WEBVIEWCORE.trigger('failed', that.handlerId, errorCode,errorMsg)

```
