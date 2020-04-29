# 插件：编写插件

3 步即可编写一个插件

> 请勿忘记引入文件 Qt.include('xxx.js')

初始化(目前已自动初始化)

```js
var SyberOS = new Syber(root)
```

## 1. 实例化插件

方式一

```javascript
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

```javascript

function Alert(opts){
   var defaultOpts = {
    id: 'alert',
    name: 'alert',
    module: 'modal',
    methods:['alert']
    source: '../qml/alert.qml'
  }
 SyberPlugin.call(this, defaultOpts)
}

Alert.prototype = SyberPlugin.prototype

#添加到组件
SyberOS.addPlugin(new Alert());

```

## 2. 绑定插件事件

在初始化插件、后续运行时，Syber 会对插件触发一些事件（event）。插件须通过这些事件来完成自定义功能。

使用 `.on()` 方法来绑定一个事件：

```javascript
on(eventName, callback)
```

- `eventName` (必填) 字符串，事件的名字。
- `callback` (必填) 回调函数，事件被触发时执行。

例子：

`ready`为组件创建完成后执行的方法,每个插件需要绑定 `ready` 事件：来完成具体的功能实现

```javascript
myPlugin.on('ready', function() {
  console.log('My plugin ready')
})
```

## 3. 添加到 Syber

最后一步，就是将写好的插件添加到 SYBEROS 中：

```javascript
SYBEROS.addPlugin(pluginObject)
```

## 其他

### 插件返回

统一通过 webview 的 success/failed 事件进行返回

```
this.success(handlerId, { confirm: true })
this.failed(handlerId, errorCode,errorMsg)

```

```

```
