---
title: start
id: version-1.5.3-upload
original_id: upload
---

上传：上传文件资源，客户端直接发起一个 HTTP POST 请求。

上传成功则返回上传id、上传状态、文件大小等。


## syberh.upload.start(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ---------------------------------- |
| url | String |  | 是 | 上传路径 |
| filePath | String |  | 是 | 文件地址 |
| name | String |  | 是 | 文件对应的 key，开发者在服务端可以通过这个 key 获取文件的二进制内容 |
| header | Object |  | 否 | HTTP 请求 Header |
| formData | Object |  | 否 | HTTP 请求中其他额外的 form data |
| success | function |  | 否 | 回调成功 |
| fail | function |  | 否 | 回调失败 |


#### object.success回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| uploadID | String | 上传ID |
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
syberh.upload.start({
    'url': 'XXX',
    'filePath': 'XXX',
    'name': 'file',
    'header': {
        a: '123'
    },
    'formData': {
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
