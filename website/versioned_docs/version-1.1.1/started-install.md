---
title: 安装SyberOS SDK
id: version-1.1.1-started-install
original_id: started-install
---

> Syberos 应用必须在 ubuntu 64 位系统下编译打包，推荐使用 Ubuntu 14.04 版本。   


### SDK下载地址

[百度网盘](https://pan.baidu.com/s/1wxQxmD6K-SMryDiWcuXseQ) 提取码：fcxs 


**安装前请先下载好以下安装包:**

`syberos_sdk-main_dev-build354.tar.bz2`

`target-armv7tnhl-xuanwu-build782.tar.bz2`

`target-i686-xuanwu-build762.tar.bz2`  

## 安装SDK

`syberh` 提供了 `install` 指令，通过命令行的方式安装开发环境。


接下来介绍如何通过 `install` 指令完成环境的安装，安装开发环境前，请确保已安装最新的 [`CLI`](started-cli.html) 工具。

### 安装 sdk

执行 `install` 指令

```bash
$ syberh install
```
按照步骤输入安装类型、安装的路径、sdk安装包的路径、当前用户密码后安装,如下图所示

![install sdk](/img/install_sdk/install_sdk.png)


### 安装 target

>安装 target 前，需要先安装 sdk。

下载target安装包，可选择对应的版本下载，通常下载 `xuanwu` 版本。

target包: 

`target-armv7tnhl-xuanwu-build782.tar.bz2`

`target-i686-xuanwu-build762.tar.bz2`

执行 `install` 指令

```bash
$ syberh install
```

![install sdk](/img/install_sdk/install_target.png)


### 注意事项

target 分为 i686 和 armv7 两种 CPU 架构，通常 i686 版本应用在模拟器上，而 armv7 版本应用在真实手机，所以若需要使用模拟器运行应用，请下载并安装 i686 版本。
