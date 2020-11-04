---
title: APP 配置
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
  # 修改项目的www目录（默认是根目录下www目录）
  "webPath": "www"
  # 当前使用的设备target
  "target": "target-armv7tnhl-xuanwu",
  # 使用的虚拟机target
  "targetSimulator": "target-i686-xuanwu",
  # 项目的sopid
  "sopid": "com.syberos.example",
  # 企业商店url(需要修改成自己的)
  "storeBaseUrl": "https://storeinner.syberos.com",
  "homePage": "",
  "deployIP": "192.168.100.100",
  "deployPort": "22",
  "devServerIP": "192.168.100.101",
  "devServerPort": "4399",
  "debuggingPort": "9867",
  "statusBar": {
    "show": true,
    "style" : "black"
  }
}
```

## homePage

> 默认访问的地址,如果为空则会访问www/index.html
```javascript
{
  //使用https://baidu.com进行访问
  "homePage": "https://baidu.com"
}
```

## statusBar

> 状态栏相关设置
```json
//默认状态栏显示状态为show,
"statusBar": {
    "show": true,  //false为不显示状态栏
    "style" : "black" //状态栏的颜色,默认为black,可配置为black,white,transwhite,transblack
  }
```
## webPath

> 可以配置指定目录（必须放在根目录下，并且首页是`index.html`）

```javascript
{
  "webPath": "dist"
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

## storeBaseUrl

> 企业商店基础url（部署在你们公司的服务器url），在`企业商店-》设置`中可以找到

使用[应用更新](/docs/apis/update/check.html) 功能，需要修改此项
