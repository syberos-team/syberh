---
title: 安装 CLI
id: version-1.1.1-alpha.2-started-cli
original_id: started-cli
---

## 安装

Syberh 项目基于 node，请确保已具备较新的 node 环境（>=8.0.0,推荐使用`v10.16.2`)，强烈建议使用 node 版本管理工具 [nvm](https://github.com/creationix/nvm) 来管理 node，这样不仅可以很方便地切换 node 版本，而且全局安装时候也不用加 sudo 了。

### cli 工具安装

首先，你需要使用 npm 或者 yarn 全局安装`@syberos/cli`，或者直接使用[npx](https://medium.com/@maybekatz/introducing-npx-an-npm-package-runner-55f7d4bd282b):

安装 yarn

```bash
npm install -g yarn
```
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
# OR 安装了 cnpm，使用 cnpm 安装 CLI
$ cnpm install -g @syberos/cli@1.1.0
```
### 注意事项

值得一提的是，如果安装过程出现`sass`相关的安装错误，请在安装[`mirror-config-china`](https://www.npmjs.com/package/mirror-config-china)后重试。

```bash
$ npm install -g mirror-config-china
```


## 更多

CLI更多详见[具体说明](./cli-readme.html)
