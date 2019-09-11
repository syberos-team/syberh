---
title: syberh 介绍
---

## 简介

syberh 框架是对 SyberOS 中支持 Hybrid 开发解决方案，基于 WebView UI 的方案进行实现。syberh 框架主要包括 CLI(开发工具)、JS SDK 和Native SDK 模块。

## 实现原理

Hybrid App 的本质，其实是在原生的 App 中，使用 WebView 作为容器直接承载 Web 页面。因此，最核心的点就是 Native 端 与 H5 端 之间的双向通讯层，其实这里也可以理解为我们需要一套跨语言通讯方案，来完成 Native(Qt/Java/xxx) 与 JavaScript 的通讯。这个方案就是我们所说的 JSBridge，而实现的关键便是作为容器的 WebView，一切的原理都是基于 WebView 的机制。

![原理](/img/introduction/1.png)


## 开发工具 CLI

App 快速开发的脚手架,提供简洁的的命令,即可从 APP 的创建到发布 APP 到手机中。

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

## JS SDK

   JS端的实现,提供常用API接口提供Hybrid开发者调用远程接口。


## Native-SDK

原生功能实现,提供标准、可拓展的方式提供给JS端进行调用。
> 由于各种各样的原因，Native 容器确保核心交互以及部分重要 API 实现，关于底层容器优化等机制会一直持续完善。

主要实现了以下功能

1. 负责和 JS-SDK 的通讯
2. 通过插件的形式统一管理qml 组件功能
3. 负责和 C++代码进行通讯


## 🤝 参与共建 [![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](http://makeapullrequest.com)

请参考[贡献指南](https://github.com/syberos-team/syberh/blob/master/docs/CONTRIBUTING.md).

>强烈推荐阅读 [《提问的智慧》](https://github.com/ryanhanwu/How-To-Ask-Questions-The-Smart-Way)、[《如何向开源社区提问题》](https://github.com/seajs/seajs/issues/545) 和 [《如何有效地报告 Bug》](http://www.chiark.greenend.org.uk/%7Esgtatham/bugs-cn.html)、[《如何向开源项目提交无法解答的问题》](https://zhuanlan.zhihu.com/p/25795393)，更好的问题更容易获得帮助。


## 特别鸣谢

[![nanjingboy](https://avatars1.githubusercontent.com/u/1390888?s=100&v=4)](https://github.com/nanjingboy/) | [![jsNewbee](https://avatars3.githubusercontent.com/u/20449400?s=100&v=4)](https://github.com/js-newbee/) | [![Qiyu8](https://avatars2.githubusercontent.com/u/15245051?s=100&v=4)](https://github.com/Qiyu8/)
:---:|:---:|:---:
[nanjingboy](https://github.com/nanjingboy/) | [jsNewbee](https://github.com/js-newbee/) |  [Qiyu8](https://github.com/Qiyu8/)

## 贡献者们

感谢以下所有给 syberh 贡献过代码的开发者：

- 感谢 quickhybrid 作者提供了 jsbridge 的实现逻辑和相关代码
- 参与者 <a href="https://github.com/syberos-team/syberos-hybrid/graphs/contributors">更多</a>

## 开发计划

[开发计划]()

## 更新日志

本项目遵从 [Angular Style Commit Message Conventions](https://gist.github.com/stephenparish/9941e89d80e2bc58a153)，更新日志由 `conventional-changelog` 自动生成。完整日志请点击 [CHANGELOG.md](./CHANGELOG.md)。

## 开发交流

[官方交流微信群]()