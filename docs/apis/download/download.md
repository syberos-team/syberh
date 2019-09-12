---
title: start
---

下载：下载文件资源到本地，客户端直接发起一个 HTTP GET 请求，返回文件的本地路径。

可以设置文件地址、文件名称等。下载成功则返回下载id、文件路径、文件状态、文件大小等。


## syberh.download.start(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ---------------------------------- |
| url | String |  | 是 | 文件地址 |
| name | String |  | 是 | 文件名称 |
| storage | String | internal | 否 | 文件存储位置（internal：内置存储卡，extended：外置存储卡） |
| success | function |  | 否 | 回调成功 |
| fail | function |  | 否 | 回调失败 |


#### object.success回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| downloadID | String | 下载ID |
| path | String | 文件路径 |
| status | String | 状态（1：开始，2：下载中，3：完成） |
| received | number | 已下载大小 |
| total | number | 总大小 |


#### object.fail回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |


### 示例代码
```javascript
syberh.download.start({
    'url': 'http://xx/xx/xx.exe',
    'name': 'xxx.exe',
    success: function(result) {
        console.log('success',result.path);    
    },
    fail: function(error) {
        console.log('fail: ', error.code, error.msg);
    }
});
```
