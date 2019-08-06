## 网络请求
> 发起网络请求

### 入参

属性 | 类型 | 必填 | 描述
---|---|---|---
url | String | 是 | 目标服务器 URL
headers | Object | 否 | 设置请求的 HTTP 头对象，默认 {'content-type': 'application/json'}，该对象里面的 key 和 value 必须是 String 类型
method | String | 否 | 默认GET，目前支持GET/POST
data | Object | 否 | 详见 data 参数说明
timeout | Number | 否 | 超时时间，单位 ms，默认 30000
dataType | String | 否 | 期望返回的数据格式，默认 json，支持 json，text，base64
success | Function | 否 | 调用成功的回调函数
fail | Function | 否 | 调用失败的回调函数
complete | Function | 否 | 调用结束的回调函数（调用成功、失败都会执行）

### data 参数说明

> 传给服务器的数据最终会是String类型，如果data不是String类型，会被转换成String。转换规则如下：

- 若方法为GET，会将数据转换成 query string： 
- encodeURIComponent(k)=encodeURIComponent(v)&encodeURIComponent(k)=encodeURIComponent(v)...
- 若方法为 POST 且 headers['content-type'] 为 application/json ，会对数据进行 JSON 序列化
- 若方法为 POST 且 headers['content-type'] 为 application/x-www-form-urlencoded ，会将数据转换成 query string： encodeURIComponent(k)=encodeURIComponent(v)&encodeURIComponent(k)=encodeURIComponent(v)...

### success 回调函数

> 入参为 Object 类型，属性如下：


属性 | 类型 | 描述
---|---|---
data | String | 响应数据，格式取决于请求时的dataType参数，如果dataType值为base64时，返回的是符合[data URI scheme](https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/Data_URIs)规范的内容字符串
status | Number | 响应码
headers | Object | 响应头

### 结果码

结果码 | 描述
---|---
11 | 无权跨域。
12 | 网络出错。
13 | 超时。
14 | 解码失败。
19 | HTTP错误。
20 | 请求已被停止/服务端限流。

> 当入参dataType值为json时，框架会先对返回结果做JSON.prase操作，如果解析失败，则会返回error为14的错误。当入参dataType值为text时，如果返回的内容格式不符，也会返回error为14的错误。当入参dataType值为base64时，如果转换失败，也会返回error为14的错误。遇到此错误时，请先检查dataType的设置是否正确。

### 示例代码

```javascript
// dataType 为 json 示例
syber.request({
  url: 'https://*',
  method: 'POST',
  data: {
    from: 'from',
    production: 'production',
  },
  dataType: 'json',
  success: function(res) {
    console.log(res);
  },
  fail: function(res) {
    console.log(res);
  },
  complete: function(res) {
    console.log(res);
  }
});

// dataType 为 base64 示例
syber.request({
  url: 'https://*/img/A*G1kWSJbe2zEAAAAAAAAAAABjARQnAQ',
  method: 'GET',
  dataType: 'base64',
  success: (resp) => {
    console.log('resp data length', resp.data.length);
    console.log('resp data', resp.data); // 返回格式类似于：data:image/png;base64,iVBORw0KG...
  },
  fail: (err) => {
    console.log('error', err);
  },
});
```

### 返回值 RequestTask

> 网络请求任务对象。调用syber.request后返回的请求对象

### RequestTask.abort()

> 中断请求任务。

### 示例代码

```javascript
// 返回 RequestTask，可以调用 abort 方法取消请求
const task = syber.request({url: 'https://*'})
task.abort();
```

