---
title: SyberOS-Hybrid 介绍
---

## 简介

SyberOS-Hybrid 框架是在 SyberOS 上支持 Hybrid 开发解决方案，基于 WebView UI 的方案进行实现。SyberOS-Hybrid 框架主要包括 CLI(开发工具)、JS-SDK、Native-SDK 模块。

## 实现原理

Hybrid App 的本质，其实是在原生的 App 中，使用 WebView 作为容器直接承载 Web 页面。因此，最核心的点就是 Native 端 与 H5 端 之间的双向通讯层，其实这里也可以理解为我们需要一套跨语言通讯方案，来完成 Native(Qt/Java/...) 与 JavaScript 的通讯。这个方案就是我们所说的 JSBridge，而实现的关键便是作为容器的 WebView，一切的原理都是基于 WebView 的机制。

![原理](/img/introduction/1.png)

```js
//核心代码
if (os.syber) {
  navigator.qt.postMessage(messageStr);
} else {
  // 浏览器
  warn(`浏览器中jsbridge无效,对应scheme:${messageStr}`);
}
```

## 开发工具CLI

App快速开发的脚手架,提供简洁的的命令,即可从APP的创建到发布APP到手机中。

创建模板项目
```bash
$ syberos init myapp
```

打包项目
```bash
$ syberos build --type device
```

快速检查用户本地开发环境
```bash
$ syberos doctor
```

## JS-SDK

不同于一般混合框架的只包含 JSBridge 部分的前端实现，本框架的前端实现包括 JSBridge 部分、多平台支持，统一预处理等等。

### 项目的结构

整个项目基于 ES6、Airbnb 代码规范，使用 webpack 构建，部分重要代码进行了 Karma + Moch a单元测试

整体目录结构如下：

```
jsbridge
    |- dist             // 发布目录
    |   |- syber.min.js
    |   |- syber.h5.js
    |- src              // 核心源码
    |   |- api          // 各个环境下的api实现 
    |   |   |- h5       // h5下的api
    |   |   |- native   // quick下的api
    |   |- core         // 核心控制
    |   |   |- ...      // 将核心代码切割为多个文件
    |   |- inner        // 内部用到的代码
    |   |- util         // 用到的工具类
    |- test             // 单元测试相关
    |   |- unit         
    |   |   |- karma.xxx.config.js
    |   |- xxx.spec.js
    |   |- ...
```

### 统一的预处理

`API多平台的支撑` 中有提到如何基于 Object.defineProperty 实现一个支持多平台调用的 API，实现起来的 API 大致是这样子的。同时也规定了 API 接口后续模块的统一规范开发。

```js
Object.defineProperty(apiParent, apiName, {
    configurable: true,
    enumerable: true,
    get: function proxyGetter() {
        // 确保get得到的函数一定是能执行的
        const nameSpaceApi = proxysApis[finalNameSpace];
        // 得到当前是哪一个环境，获得对应环境下的代理对象
        return nameSpaceApi[getCurrProxyApiOs(quick.os)] || nameSpaceApi.h5;
    },
    set: function proxySetter() {
        alert('不允许修改syber API');
    },
});

//...

syber.extendModule('modal', [{
    namespace: 'alert',
    os: ['syber'],
    defaultParams: {
        message: '',
    },
    runCode(message) {
        alert('syber-' + message);
    },
}]);
```

### 最终效果

框架设计的最终目的是提供给用户一个简单易用的API,同时也可以保证开发者可以依托目前的模式进行API的拓展开发。

最终使用的示例如下:

```js
syber.modal.alert({
  content: 'This is a alert',
  success: fucntion(result) {  
      console.log(result)
  },
  fail: fucntion(error) {
        console.log(error.code)
        console.log(error.msg)
  }
})
```

## Native-SDK

Hybrid 模式的核心就是在原生。由于各种各样的原因，本项目中的 Native 容器确保核心交互以及部分重要 API 实现，关于底层容器优化等机制后续再考虑完善。

### 项目的结构

```
api
    |- qml
    |- js
    |- src
```

主要实现了以下功能
1. 负责和JS-SDK的通讯
2. 通过插件的形式统一管理目前实现的qml组件功能。
3. 负责和C++代码进行通讯
