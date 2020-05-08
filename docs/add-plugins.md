---
title: 拓展插件
---

拓展插件分为2步: 
1. 拓展JS-SDK
2. 拓展Native-SDK

## 拓展JS-SDK
在Syberh v2.0版本中, 提供新的插件机制。

优点:
- Plugin实现，代码更清晰
- 不需要在JSBridge源码中进行开发，减少耦合
- 扩展应用级别的插件时，只需要将编写好的插件放置在syberh.min.js之后加载即可

### 示例
```javascript
// custom.plugin.js
function AudioPlugin(){}

// 模块名, 必须实现
AudioPlugin.prototype.module = function(){
    return 'audio'
}

// 运行环境,默认是syberos环境, 必须实现的方法
AudioPlugin.prototype.os = function(){
    return ['syberos']
}

// 模块的方法, 返回的是默认值, 格式是method_[name]
AudioPlugin.prototype.method_start = function(){
    return {path:'', position:0}
}
```

## 拓展Native-SDK

C++插件里面分为`C++插件`和 `C++和QML混合插件`

插件可以看成一个动态链接库（Linux 上的 *.so 文件）, 最基本的插件是一个共享库，从开发者的角度，插件是一个模块。

Syberh 插件模块的实现需要满足以下功能：
- 在一个类中实现ExtensionSystem::IPlugin接口。
- 提供一个pluginspec(json格式)插件描述文件，用于描述插件的元信息



### 示例
通过syberh init创建的项目, 在`platforms/syberos/syberh-plugins`目录下, 新建一个[C++共享库](/docs/library.html)

1. 首先需要在根目录下建一个`plugin.json`
```json
{
  // 插件名(唯一, 并且不能是C++关键字)
  "Name": "App",
  // 	插件版本号
  "Version": "1.0.0",
  // 兼容Qt版本
  "CompatVersion":"5.3",
  // 版权声明
  "Copyright": "(C) 2014-2020 syberos.com",
  // 许可证类型
  "License": "MIT",
  // 包的官方URL
  "Url": "https://syberh.syberos.com",
  // 包的描述信息
  "Description": "Syberh全局配置模块"
}
```

| 属性名    | 属性含义     | 必须 | 	示例   |
| ------- | -------- | -------- | -------- |
| Name | 唯一, 并且不能是C++关键字 | 是 | Download |
| Version | 插件版本号 | 是 | 	1.0.0  |
| CompatVersion | 兼容Qt版本<br> compatibility version <= dependency version <br> <= plugin version | 是 | 5.3.0  |
| Copyright | 版权声明 |  | (C) 2014-2020 syberos.com  |
| License | 许可证类型 |  | MIT  |
| Url | 包的官方URL |  |   |
| Description | 插件描述 |  | Syberh全局配置模块  |


2. 修改项目的pro文件
```C++
// 添加模块(根据自己需要添加)
QT       += gui widgets quick qml

// 添加pkg-config
CONFIG += link_pkgconfig
// 添加C++11
CONFIG += C++11
// 插件编译后只生成一个so文件
CONFIG += plugin

// 通过pkg-config链接元心库
PKGCONFIG += syberos-qt

// 一般QML插件需要用到syberos-application库
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../syberos_application
LIBS += -L/usr/lib -lsyberos-application

// 添加nativesdk和pluginmanager头文件 (这样写cli打包的时候,会转换成真正的路径)
INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

// 添加nativesdk和pluginmanager头文件 (这样写是为了让编辑器找到头文件, 可以点击进去, 插件调试完成以后可以去掉)
INCLUDEPATH += /example/platforms/syberos/nativesdk/src
INCLUDEPATH += /example/platforms/syberos/pluginmanager/src

// 添加nativesdk和pluginmanager库
LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager

// 打包后的so文件路径
DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)
```

3. 编写头文件
插件类必须集成`IPlugin`

iplugin提供了多个虚函数: `initialize()`, `extensionsInitialized()`, `delayedInitialize()`, `invoke()`, `SignalManager()`
- `invoke()` 是接受用户调用该插件的方法, 可以接受到callbackID, actionName(请求的方法名), params(带的参数)
- `SignalManager()` 信号管理类, 提供了4个信号, 分别是:　`success()`, `failed()`, `subscribe()`

```C++
// iplugin.h
#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "iplugin_global.h"

#include <QObject>
#include <QVariantMap>
#include <QtPlugin>

namespace ExtensionSystem {

namespace Internal {
    class IPluginPrivate;
    class PluginSpecPrivate;
}

class PluginManager;
class PluginSpec;
class SignalManager;

class IPLUGIN_EXPORT IPlugin : public QObject
{
    Q_OBJECT
public:
    enum ShutdownFlag {
        SynchronousShutdown,
        AsynchronousShutdown
    };

    IPlugin();
    ~IPlugin() override;

    virtual bool initialize(const QStringList &arguments, QString *errorString);
    virtual void extensionsInitialized();
    virtual bool delayedInitialize() { return false; }
    virtual ShutdownFlag aboutToShutdown() { return SynchronousShutdown; }
    virtual QObject *remoteCommand(const QStringList & /* options */,
                                   const QString & /* workingDirectory */,
                                   const QStringList & /* arguments */) { return nullptr; }
    virtual QVector<QObject *> createTestObjects() const;

    PluginSpec *pluginSpec() const;

    //插件接受JS SDK调用方法,需要实现该方法，处理插件逻辑
    virtual void invoke(QString callbackID, QString action, QVariantMap params);
    //信号管理类，通过该类来绑定插件中的信号
    SignalManager* signalManager();
signals:
    void asynchronousShutdownFinished();

private:
    Internal::IPluginPrivate *d;

    friend class Internal::PluginSpecPrivate;
};


class SignalManager : public QObject {
    Q_OBJECT
public:
    SignalManager();
    ~SignalManager();

signals:
    void success(long callbackID, QVariant result);
    void failed(long callbackID, long errorCode,QString errorMsg);
    void progress(long callbackID, const int totalLength, const int progress, const int status);
    void subscribe(QString handleName, QVariant result);

};

}
#endif // IPLUGIN_H
```


插件类必须继承ExtensionSystem::IPlugin

插件的IID是固定写法, "com.syberos.syberh.SyberhPlugin"

插件的FILE是固定写法, 用来存放插件的元数据, `plugin.json`位于项目根目录下

```C++
#ifndef APP_H
#define APP_H

// 必须引入
#include <QObject>
#include <QtPlugin>
#include "iplugin/iplugin.h"

#include "app_global.h"

class APPSHARED_EXPORT App : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    // 插件的固定写法,IID,FILE不可变
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    App();
    // 接收用户调用该模块的所有参数
    void invoke(QString callbackID, QString actionName, QVariantMap params);
    // 自定义方法
    void setAppOrientation(QString callbackID, QVariantMap params);
};

#endif // APP_H
```

4. 编写源文件
- 返回成功或者失败信号通过`signalManager()->success()` 或者 `signalManager()->failed()`  方法, 失败信号我们在`framework/common/errorinfo.h`中, 封装了常见的错误码, 使用时需要添加命名空间`NativeSdk`

```C++
#include "app.h"
#include "framework/common/errorinfo.h"
#include "qmlmanager.h"
#include <SyberosGuiCache>

// 添加命名空间(使用NativeSdk都需要添加此命名控件)
using namespace NativeSdk;

App::App()
{
}

void App::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    // actionName 是js调用的方法名, 格式是syberh[模块名][方法名]
    if (actionName == "setAppOrientation") {
        setAppOrientation(callbackID, params);
    }
}

void App::setAppOrientation(QString callbackID, QVariantMap params)
{
    // 返回成功信号
    signalManager()->success(callbackID.toLong(), true);
}
```

5. 编译

在syberh创建的项目中,使用`npm run dev:device` 进行编译, 写好相应的js代码进行验证(暂时不可以直接在编辑器中调试, 会提示找不到nativesdk和pluginmanager库)

### QML插件
有些插件功能必须通过界面展示, 所以有了QML模块


QML插件分为两种:
1. 一种是当前页面显示或隐藏的
   - 需要使用`create()`创建, 使用`destroy()`销毁
2. 一种是进入到一个新页面
   - 最外层必须是`CPage{}`
   - 需要使用`open()`打开, 使用`close()`关闭


Syberh框架在`NativeSdk`下提供了`QmlManager`类, 用来操作qml
- 通过`create()` 或者 `open()` 创建qml
- 通过`destroy()` 或者 `close()` 销毁qml
- 通过`setProperty(QmlObject, key, value)`, 设置qml的属性值
- 通过`call()` 执行qml中的函数或者方法, 可以接受方法的返回值
- 通过`connectSignal()` 连接信号, 用法和`connect()`一样
- 通过`signalManager()` 返回多个信号(常用的是: 成功信号和失败信号)


一种是像`modal`模块这样, 一种是像`filepicker`模块, 具体区别如下:

- `modal`模块下的`toast`方法
```C++
// SToast.qml
Rectangle {
  function show(title, icon, duration) {
    // 具体代码...
  }
}
```

```C++
  QmlManager qmlManager;
  // 创建一个modal模块下的SToast.qml, create第二个参数表示在qml组件创建在当前Item上
  QmlObject *toastQml = qmlManager.create("qrc:/qml/SToast.qml", qmlManager.currentItem());
  
  // 通过qmlManager.call()执行SToast.qml中的show()方法, 这里需要注意字符串拼接
  QVariant result = qmlManager.call(toastQml, "show('"+ title + "','" + icon + "','" + duration +"')");

  // 接收qmlManager.call()执行结果, 来判断是成功还是失败 (SToast.qml中show()出错会返回错误码)
  QString errorMsg = result.toString();
  if (errorMsg.isEmpty()) {
      // 返回成功信号,并且销毁qml组件
      signalManager()->success(callbackID.toLong(), "");
      qmlManager.destroy(toastQml);
  } else {
      // 返回失败信号,并且销毁qml组件
      signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidParameter, errorMsg);
      qmlManager.destroy(toastQml);
  }
```

- `filepicker`模块下的`open`方法, 最外层必须是`CPage{}`
```C++
// SFilesPicker.qml
CPage {
  property string titleText: ""
  signal cancel()
  signal ok(string filesPath)
}
```

```C++
  filepickerQml = qmlManager.open("qrc:/qml/SFilesPicker.qml");
  // 给QML属性赋值
  qmlManager.setProperty(filepickerQml, "titleText", title);
  // 连接qml信号(和C++ connect()连接信号用法一样)
  qmlManager.connectSignal(filepickerQml, SIGNAL(ok(QString)), this, SLOT(chooseOk(QString)));
  qmlManager.connectSignal(filepickerQml, SIGNAL(cancel()), this, SLOT(chooseCancel()));
```

```C++
// QML信号返回数组或者对象的时候, 建议返回json字符串
// 在C++层转化成QJsonArray或者QJsonObject, 再转换成QVariant类型, 在成功信号里面返回
void Filepicker::chooseOk(QString filesPath)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(filesPath.toUtf8());
    if (jsonDocument.isNull()) {
        // 返回失败信号
        signalManager()->failed(globalCallbackID, ErrorInfo::PluginError, "返回数据格式错误");
    }
    // json字符串转换为QJsonObject
    QJsonObject result = jsonDocument.object();
    // 发出成功信号
    signalManager()->success(globalCallbackID, QVariant(result));
    // 全局callbackID重置
    globalCallbackID = 0;
    // 关闭qml页面, 并且销毁
    qmlManager.close(filepickerQml);
}
```


## 如何使用
> JS-SDK 和 Native-SDK 都实现了, 就可以开始使用了

1. 使用时，先引入 syberh.min.js，再引入扩展的插件
```javascript
<script type="text/javascript" src="lib/syberh.min.js"></script>
<script type="text/javascript" src="custom.plugin.js"></script>
```

2. 注册插件：
```javascript
syberh.register(AudioPlugin)
```

3. 开始使用:
```javascript
syberh.audio.start({
  path: "/home/user/audio/xxx.aac",
  success: function(result){
    console.log('success', result);  
  },
  fail: function(error){
    console.log('fail: ', error.code, error.msg);
  }
})
```