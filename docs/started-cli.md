---
title: CLI安装及使用
---

## 安装

Syberh 项目基于 node，请确保已具备较新的 node 环境（>=8.0.0），推荐使用 node 版本管理工具 [nvm](https://github.com/creationix/nvm) 来管理 node，这样不仅可以很方便地切换 node 版本，而且全局安装时候也不用加 sudo 了。

### cli 工具安装

首先，你需要使用 npm 或者 yarn 全局安装`@syberos/cli`，或者直接使用[npx](https://medium.com/@maybekatz/introducing-npx-an-npm-package-runner-55f7d4bd282b):

```bash
# 使用 npm 安装 CLI
$ npm install -g @syberos/cli
# OR 使用 yarn 安装 CLI
$ yarn global add @syberos/cli
# OR 安装了 cnpm，使用 cnpm 安装 CLI
$ cnpm install -g @syberos/cli
```

### 回到某个版本
需要安装某个固定版本，或者回到某个版本，例如我们要安装 1.1.0 ， 则如下：
```bash
# 使用 npm 安装 CLI
$ npm install -g @syberos/cli@1.1.0
# OR 使用 yarn 安装 CLI
$ yarn global add @syberos/cli@1.1.0
# OR 安装了 cnpm，使用 cnpm 安装 CLI
$ cnpm install -g @syberos/cli@1.1.0
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
$ syberh init myApp
```

![syberos init myApp command screenshot](/img/init_myapp.png)

在创建完项目之后，会默认开始安装项目所需要的依赖，安装使用的工具按照 yarn>cnpm>npm 顺序进行检测，一般来说，依赖安装会比较顺利，但某些情况下可能会安装失败，这时候你可以在项目目录下自己使用安装命令进行安装,如

```bash
# 使用 yarn 安装依赖
$ yarn
```

进入项目目录开始开发

> 目前暂无对前端开发工具进行限制,但是建议使用[`vs code`](https://code.visualstudio.com/)进行代码开发,后续我们也会提供vs code相关插件使得可以更好的运行调试


### 编译打包

开发过程中可以使用真机或者模拟器运行应用

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

## 更新

Syberh 提供了更新命令来更新 CLI 工具自身和 升级到最新的core

更新 Syberh CLI 工具
```bash
#syberh
$ syberh update self
# npm
$ npm i -g @syberos/cli@latest
# yarn
$ yarn global add @syberos/cli@latest
```

更新项目中 Syberh 相关的依赖

```bash
$ syberh update project
```


### 环境及依赖检测
Syberh 提供了命令来一键检测 Syberh 环境及依赖的版本等信息，方便大家查看项目的环境及依赖，排查环境问题。

#### Syberh Doctor

Syberh Doctor 就像一个医生一样，可以诊断项目的依赖、设置、结构，以及代码的规范是否存在问题，并尝试给出解决方案。

只需要在终端运行命令：syberh doctor：

```bash
$ syberh doctor
```

## API 列表

### init [projectName]
> 初始化项目

| 参数 | 描述 |
| ---  | --------- |
| --description [description] | 项目介绍    |
| --example      | 创建示例项目 |

``` bash
# 初始化项目
$ syberh init myapp
# 创建示例项目
$ syberh init --example
```

### build
> 打包运行项目

| 参数 | 描述 |
| ------  | ----------- |
| --type [typeName]      | 运行编译类型,device:真机 simulator:模拟器    |
| --debug                | debug模式运行,支持热更新    |
| --target [targetName]  | 重置target,device:真机 simulator:模拟器    |
| --env [env]            | Env type    |
| --port [port]          | Specified port    |

``` bash
# 打包并跑在真机上
$ syberh build --type device
# debug模式，打包并跑在真机上
$ syberh build --type device --debug
```

### update
> 更新cli工具或者更新核心文件

| 参数 | 描述 |
| ------  | ----------- |
| self      | 更新cli工具    |
| project      | 更新当前项目核心文件    |

``` bash
$ syberh update self
```

### doctor
> 快速检查用户本地开发环境

``` bash
$ syberh doctor
```

### simulator
> 启动模拟器

``` bash
$ syberh simulator
```

### install
> 通过命令行模式安装sdk和target

``` bash
$ syberh install
```
