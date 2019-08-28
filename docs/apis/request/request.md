---
title: request
---

网络请求：发起网络请求。

可以设置请求地址、请求类型、请求参数等。返回值由请求地址决定，支持json/text格式。

支持`Promise` 使用。


## syber.netWork.request(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| url | String |  | 是| 目标服务器 URL |
| method | String | GET | 否 |请求类型，支持GET/POST/PUT/DELETE |
| dataType | String | json | 否 | 返回格式，json/text |
| headers | Object | | 否 | 例：{"key","val"} |
| data | Object | | 否 | 参数，例：{"key","val"} |
| success | function |  |  否     | 回调成功      |
| fail   | function |  |  否     | 回调失败      |


#### object.fail回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |


### 示例代码

```javascript
syber.netWork.request({
    url: 'https://*',
    success: function(result) {
        console.log('success',result);            
    },
      fail: function(error) {
        console.log('fail: ', error.code, error.msg);
    }
});
```

#### Promise
```javascript
syber.netWork.request({
        url: 'https://*',
    }).then(function(result) {
        console.log('success',result); 
    }).catch(function(error) {
        console.log('fail: ', error.code, error.msg);
    });
```

