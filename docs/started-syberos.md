---
title: 安装 SyberOS SDK & PKD
---

## 安装

Syberos 应用必须在 ubuntu 64位系统下编译打包，推荐使用 Ubuntu 14.04 版本。安装 SyberOS SDK & PKD 前请选确保当前系统为 Ubuntu。


**下载地址：**

[百度网盘](https://pan.baidu.com/s/1wxQxmD6K-SMryDiWcuXseQ) 提取码：fcxs 

### 安装 SDK

下载依赖包 `sdk_install_package.tgz`，解压并进行安装，安装时需要root权限

```bash
# 将 sdk_install_package.tgz 解压至当前目录
$ tar zxvf sdk_install_package.tgz
# 切换进解压后的目录中
$ cd sdk_install_package/ubuntu14.04
# 安装依赖
$ sudo dpkg -i *.deb
```

接下来安装 SDK，下载 `SyberOS-sdk_compile.build253-SDK-20170220.run`，添加执行权限并运行

```bash
# 添加执行权限
$ sudo chomd a+x SyberOS-sdk_compile.build253-SDK-20170220.run
# 安装
$ ./SyberOS-sdk_compile.build253-SDK-20170220.run
```

安装过程如下：

1. 点击"下一步"
![步骤1](/img/install_sdk/1.png)

2. 点击"下一步"
![步骤2](/img/install_sdk/2.png)
> **注意**：此处不要修改路径，默认安装在用户目录下

3. 点击"下一步"
![步骤3](/img/install_sdk/3.png)

4. 同意许可，并点击"下一步"
![步骤4](/img/install_sdk/4.png)

5. 点击"下一步"
![步骤5](/img/install_sdk/5.png)

6. 等待安装完成
![步骤6](/img/install_sdk/6.png)

7. 点击"完成"
![步骤7](/img/install_sdk/7.png)


### 安装 PDK

需要先下载sdk和target包

sdk: 

`syberos_sdk-main_dev-build354.tar.bz2`

target: 

`target-armv7tnhl-xuanwu-build782.tar.bz2`

`target-i686-xuanwu-build762.tar.bz2`


1. 启动 SyberOS SDK
![步骤8](/img/install_sdk/8.png)
![步骤9](/img/install_sdk/9.png)

2. 在右侧菜单中点击"PkdManager"，并选择"本地安装"，点击"下一步"
![步骤10](/img/install_sdk/10.png)

3. 选择"安装sdk和target"，并点击"下一步"
![步骤11](/img/install_sdk/11.png)

4. 此处输入用户密码，并点击"下一步"
![步骤12](/img/install_sdk/12.png)
> **注意**：此处不要修改路径，默认安装在用户目录下

5. 选择sdk安装包
![步骤13](/img/install_sdk/13.png)

6. 选择target安装包
![步骤14](/img/install_sdk/14.png)

7. 点击"下一步"
![步骤15](/img/install_sdk/15.png)

8. 等待安装完成
![步骤16](/img/install_sdk/16.png)

9. 安装完成
![步骤17](/img/install_sdk/17.png)


### 注意事项

安装 SDK 与 PDK 时，切勿修改安装路径，SDK安装于用户目录下的 SyberOS-SDK 目录中，PDK安装于用户目录下的 Syberos-Pdk 目录中。
