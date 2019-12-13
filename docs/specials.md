---
title: 常见问题
---

## `热更新检测不到文件变化` 的问题处理

```bash
#设置 max_user_watches值
echo fs.inotify.max_user_watches=524288 | sudo tee -a /etc/sysctl.conf && sudo sysctl -p
```

## `expect` not found
> ubuntu 16版本会出现expect找不到

```bash
#安装 expect
sudo apt-get install expect
```

## syberh命令离线安装
> 在有网络情况下进行如下操作：

```bash
# 全局安装syberh
npm install -g @syberos/cli

# 找到npm包的根目录
npm root -g

# 进入目录, 找到目录下的@syberos文件夹
cd /home/xuejun/.nvm/versions/node/v12.13.0/lib/node_modules
```

> 拷贝`@syberos`目录到无网机器即可

1、拷贝`@syberos`文件夹到无网机器上

2、给npm包做软链接(源文件目录需要写到bin目录下)
```bash
ln –s  /home/xuejun/@syberos/cli/bin  syberh
```

3、开始使用
``` bash
syberh
```

## 常见调试手段
```bash
syberh init --example
```
创建一个示例项目，示例项目的www/lib下有一个[vconsole.min.js](/js/vconsole.min.js)，可以使用这个拓展工具进行调试，使用的示例参考index.html

注: 不要使用官方的vconsole.min.js，我们对这个包做了兼容处理

#### 使用文档
https://github.com/Tencent/vConsole


## vue项目中如何使用
``` javascript
import syberh from '@syberos/jsbridge'
// 注册到window对象上，可以全局使用
window.syberh = syberh
```

## 扫码在S1手机上闪退

`S1`手机因为某些原因，需要用单独的扫码模块，按下面步骤实现即可

1、在项目根目录下的`platforms/syberos/vendor`下删除`syberh-qrcode`文件夹

2、在项目根目录下的`platforms/syberos/vendor`下,下载S1手机扫码模块
```javascript
git clone -b s1 https://github.com/syberos-team/syberh-qrcode
```


## syberh升级更新项目后，跑不起来了


### 为什么会出现这个问题
`syberh`升级到`1.5.0`版本后，使用`syberh update project`命令更新项目核心代码(`platforms文件夹`)

```
CBooster::loadMain in
CBooster loadMain:  /data/apps/com.syberos.example/bin/app
CBooster loading invoked application failed:  
//出现下面这个错误
libzxing.so: cannot open shared object file: No such file or directory  
lijing loading symbol 'main' failed:  /data/apps/com.syberos.example/bin/app: undefined symbol: main
terminate called after throwing an instance of 'std::runtime_error'
  what():  CBooster: Loading symbol 'main' failed: '/data/apps/com.syberos.example/bin/app: undefined symbol: main'
```

出现这个错误，是因为我们在`1.5.0`版本上新增扫码模块，所以需要更改`/platforms/syberos/syberos.pri`文件

### 如何解决
需要在`/platforms/syberos/syberos.pri`中，新增一行配置项
```
LIB_DIR = /data/app-libs/com.syberos.example  //com.syberos.example 改成自己的sopid
```
