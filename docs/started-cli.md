---
title: 安装 cli 及使用
---

## 安装

Syberos 项目基于 node，请确保已具备较新的 node 环境（>=8.0.0），推荐使用 node 版本管理工具 [nvm](https://github.com/creationix/nvm) 来管理 node，这样不仅可以很方便地切换 node 版本，而且全局安装时候也不用加 sudo 了。

### cli 工具安装

首先，你需要使用 npm 或者 yarn 全局安装`@syberos/cli`，或者直接使用[npx](https://medium.com/@maybekatz/introducing-npx-an-npm-package-runner-55f7d4bd282b):

```bash
# 使用 npm 安装 CLI
$ npm install -g @syberos/cli
# OR 使用 yarn 安装 CLI
$ yarn global add @syberos/cli
```

### 注意事项

值得一提的是，如果安装过程出现`sass`相关的安装错误，请在安装[`mirror-config-china`](https://www.npmjs.com/package/mirror-config-china)后重试。

```bash
$ npm install -g mirror-config-china
```

## 使用

### 创建项目

使用命令创建模板项目

```bash
$ syberos init myApp
```

npm 5.2+ 也可在不全局安装的情况下使用 npx 创建模板项目

```bash
$ npx @syberos/cli init myApp
```

![syberos init myApp command screenshot](/img/init_myapp.png)

在创建完项目之后，会默认开始安装项目所需要的依赖，安装使用的工具按照 yarn>cnpm>npm 顺序进行检测，一般来说，依赖安装会比较顺利，但某些情况下可能会安装失败，这时候你可以在项目目录下自己使用安装命令进行安装

```bash
# 使用 yarn 安装依赖
$ yarn
# OR 使用 cnpm 安装依赖
$ cnpm install
# OR 使用 npm 安装依赖
$ npm install
```

进入项目目录开始开发

### 注意事项

值得一提再提的是，如果安装过程出现`sass`相关的安装错误，请在安装[`mirror-config-china`](https://www.npmjs.com/package/mirror-config-china)后重试。

```bash
$ npm install -g mirror-config-china
```

### 检查环境

```bash
$ syberos doctor
```

### 编译打包

开发过程中可以使用模拟器或真机运行应用

```bash
# 运行于模拟器
$ syberos build --type simulator

# 运行于手机
$ syberos build --type device

# 只打包不运行
$ syberos build
```

## 更新

Syberos 提供了更新命令来更新 CLI 工具自身和项目中 Syberos 相关的依赖

更新 Syberos CLI 工具

```bash
# npm
npm i -g @syberos/cli@latest
# yarn
yarn global add @syberos/cli@latest
```
