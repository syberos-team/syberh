---
title: start
---

### syber.download.start(Object object)

> 下载文件资源到本地

### 入参

> Object类型，属性如下：

属性 | 类型 | 必填 | 描述
---|---|---|---
url | String | 是 | 下载文件地址
name | String | 是 | 文件名称
success | Function | 否 | 调用成功的回调函数
fail | Function | 否 | 调用失败的回调函数

### success 回调函数

> Object类型，属性如下：

属性 | 类型 | 描述
---|---|---
downloadID | String | 下载ID
path | String | 文件路径
status | String | 状态（1：开始，2：下载中，3：完成）
received | Number | 已下载大小
total | Number | 总大小

### 示例代码
```javascript
syber.download.start({
      'url': 'http://xx/xx/xx.exe',
      'name': 'xxx.exe',
      success: function(result) {
        console.log(result);
      },
      fail: function(error) {
        console.log(error);
      }
    });
```
