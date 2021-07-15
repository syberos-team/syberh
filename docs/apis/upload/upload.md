---
title: start
---

上传：上传文件资源，客户端直接发起一个 HTTP POST (multipart/form-data) 请求。

成功发起上传后, 该接口可以通过回调持续获取上传进度。


## syberh.upload.start(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ---------------------------------- |
| url | String |  | 是 | 上传路径 |
| name | String | file | 否 | 文件域的名称, 服务端通过该值提取文件流. 默认为file |
| file | String |  | 是 | 文件本地路径 |
| cookie | Object |  | 否 | 待发送的cookie |
| header | Object |  | 否 | 待发送的HTTP请求头 |
| form | Object |  | 否 | 发送额外的表单数据 |
| success | function |  | 否 | 回调成功 |
| fail | function |  | 否 | 回调失败 |


#### object.success回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| id | String | 上传ID |
| status | String | 状态（1：开始，2：下载中，3：完成） |
| sent | number | 已上传的数据字节数 |
| total | number | 上传文件的字节总数 |
| response | Object | 服务端的响应结果, 仅在status为3时存在. 包含属性: cookie, header, body |


#### object.fail回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |


### 示例代码
```javascript
syberh.upload.start({
    'url': 'XXX',
    'name': 'file',
    'file': 'XXX',
    'cookie': {
        cookieName: 'test_cookie'
    },
    'header': {
        headerName: 'test_header'
    },
    'form': {
        name: 'syberos'
    },
    success: function(result) {
        console.log('success',result);
    },
    fail: function(error) {
        console.log('fail: ', error);
    }
});
```
