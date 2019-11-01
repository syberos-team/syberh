---
title: 常见问题
id: version-1.4.0-alpha.1-specials
original_id: specials
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

1、下载项目
```bash
# 下载最新的tag版本
git clone --branch v1.3.0 https://github.com/syberos-team/syberh
```
2、进入cli目录
```bash
cd syberh/packages/cli/
```
3、安装项目依赖
```bash
npm install
```
> 安装完成后，拷贝cli目录到无网机器即可

4、安装syberh命令
```bash
cd cli/
npm install -g
```

5、开始使用
```bash
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
