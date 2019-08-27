---
title: 第一个应用
---

## 创建一个应用

使用 @syberos/cli 工具能够快速的创建一个应用。以下说明建立在已正确安装 [`SDK & PDK`](started-syberos.html) 和 [`cli`](started-cli.html)

使用命令创建模板项目

```bash
$ syberos init myApp
```

过程如下：

![syberos init myApp command screenshot](/img/init_myapp.png)

执行完命令后，在 myApp 目录中已经为我们生成了标准项目结构。

结构如下：

```
myApp
    |- node_modules         // 依赖包
    |- platforms            // 应用目标平台原生代码
    |   |- syberos          // syberos原生实现
    |   |   |- app
    |   |   |- com/syberos/api
    |   |   |- tests
    |   |   |- META-INF
    |   |   |- app.pro
    |   |   |- syberos.pri
    |   |   |- sopconfig.xml
    |- www                  // 前端代码
    |   |- lib              // js api
    |   |- index.html       // 首页
```

开发者可选用任意前端框架开发应用，只需将最终编译完成的代码放置在 www 目录中，应用启动时会自动加载 index.html

## 运行app

运行 build 指令，将会看到 Hello,SyberOS 页面。

首次运行需经历编译过程，请稍待片刻。

```bash
# 运行在手机上
$ syberos build --type device
# 运行在模拟器上
$ syberos build --type simulator
```


