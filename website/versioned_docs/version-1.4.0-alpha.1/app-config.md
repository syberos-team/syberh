---
title: APP 配置
id: version-1.4.0-alpha.1-app-config
original_id: app-config
---

`project.config.json`配置项目相关信息

文件位于
```bash
# myapp为项目的根目录
myapp/project.config.json
```

相关配置项（所有配置项都可以修改）
```javascript
{
  # 项目名称
  "projectName": "example",
  # APP名称
  "appName": "example",
  # 修改项目的www目录（默认是根目录下www目录, 必须是相对目录）
  "webPath": "www"
  # 当前使用的设备target
  "target": "target-armv7tnhl-xuanwu",
  # 使用的虚拟机target
  "targetSimulator": "target-i686-xuanwu",
  # 项目的sopid
  "sopid": "com.syberos.example"
}
```

## webPath

> 可以将vue项目打包后的目录写在这里

```javascript
{
  "webPath": "../vuedemo/dist/index.html"
}
```

## target

修改方式有二种：

方式一： 

    修改配置文件中target为已安装的target

方式二： 
```bash
# 通过命令行选择本地已安装的target
syberh build --type device 
```
