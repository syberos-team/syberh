---
title: 第一个应用
id: version-1.1.1-first-app
original_id: first-app
---

## 创建一个应用

使用 @syberos/cli 工具能够快速的创建一个应用。以下说明建立在已正确安装 [`SDK & PDK`](started-install.html) 和 [`CLI`](started-cli.html)

使用命令创建模板项目

```bash
$ syberh init myApp
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
    |   |- lib              // js sdk
    |   |- index.html       // 首页
```

> 开发者原则上是可选用任意前端开发工具进行开发，只需将最终编译完成的代码放置在 www 目录中，应用启动时会自动加载 index.html

>但是建议使用[`vs code`](https://code.visualstudio.com/)进行代码开发,后续我们也会提供vs code相关插件使得可以更好的运行调试和代码提示

## 运行app

运行 build 指令，将会看到 Hello,SyberOS 页面。

首次运行需经历编译过程，请稍待片刻。

```bash
$ cd 项目目录
# 调试模式运行于真机
$ yarn run dev:device
# 调试模式运行于真机
$ yarn run dev:simulator
# 运行于真机
$ yarn run build:device
# 运行于模拟器
$ yarn run build:simulator
# 只打包不运行
$ yarn run build
```

## 进阶
 
 

## 修改图标

应用的图标位于 `platforms/syberos/app/res/app.png` 

通过替换该图片完成应用图标的修改，[具体配置](./app-config.html)

