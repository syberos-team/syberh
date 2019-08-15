---
title: request
---

### syber.network.request(Object object)

> 发起网络请求

### 入参

> Object类型，属性如下：

属性 | 类型 | 必填 | 描述
---|---|---|---
url | String | 是 | 目标服务器 URL
method | String | 否 | 默认GET，目前支持GET/POST
data | Object | 否 | 例：{"key","val"}
success | Function | 否 | 调用成功的回调函数
fail | Function | 否 | 调用失败的回调函数


### success 回调函数

> 入参为 Object 类型，属性如下：


属性 | 类型 | 描述
---|---|---
data | String | 响应数据


### 示例代码

```javascript
syber.network.request({
  url: 'https://*',
  method: 'POST',
  data: {
    'from': 'from',
    'production': 'production',
  },
  success: function(res) {
    console.log(res);
  },
  fail: function(res) {
    console.log(res);
  }
});

syber.network.request({
  url: 'https://*',
  method: 'POST',
  data: {
    'from': 'from',
    'production': 'production',
  }
}).then(function(res) {
    console.log(res);
}).catch(function(res) {
    console.log(res);
});

```

