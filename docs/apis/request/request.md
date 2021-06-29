---
title: request
---

网络请求：发起网络请求。

可以设置请求地址、请求类型、请求参数等。返回值由请求地址决定，支持json/text格式。不支持响应内容为二进制格式。

<!-- 支持`Promise` 使用。 -->


## syberh.network.request(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| url | String |  | 是 | 目标服务器 URL |
| method | String | | 是 |请求类型，支持GET/POST/PUT/DELETE |
| dataType | String | text | 否 | 设置响应参数中的data类型，json/text |
| header | Object | | 否 | 设置请求的header。若未设置Content-Type，默认为 application/x-www-form-urlencoded |
| cookie | String/Object | | 否 | 设置请求时发送的cookie。使用String类型时为原始字符串格式（例：logincookie=dha1gIk5bA; path=/; secure; HttpOnly），使用Object类型时为键值对（例：{logincookie:"dha1gIk5bA"}） |
| data | String/Object | | 否 | 请求时发送的内容，发送键值对参数时使用Object类型，发送json格式参数使用String类型 |
| success | function |  |  否     | 回调成功      |
| fail   | function |  |  否     | 回调失败      |


#### object.success回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| statusCode | String | 响应状态码 |
| header | Object  | 响应头信息 |
| cookie | Object  | 请求的cookie。若发生重定向，会尝试获取响应头中的Set-Cookie存入其中 |
| data | Object/String  | 响应数据类型取决于dataType，如dataType为json此时为Object类型 |


#### object.fail回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |


### 示例代码

```javascript

syberh.network.request({
    url: 'https://*',
    method: 'get',
    success: function(result) {
        console.log('success',result.statusCode, result.header, result.cookie, result.data);
    },
      fail: function(error) {
        console.log('fail: ', error.code, error.msg);
    }
});
```

<!-- #### Promise
```javascript
syberh.network.request({
        url: 'https://*',
    }).then(function(result) {
        console.log('success',result); 
    }).catch(function(error) {
        console.log('fail: ', error.code, error.msg);
    });
``` -->

