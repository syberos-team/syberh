---
title: launchApp
---

## syberh.runtime.launchApp(Object object)

一个应用希望启动另一个应用时调用，支持Promise调用

### 参数

**Object object**

| 属性    | 类型     | 是否必填         | 描述     |
| ------- | -------- | ---------------- | -------- |
| url     | String   | url或者appid必填 | url      |
| appid   | String   | url或者appid必填 | appid    |
| params  | Array    | 否               | 参数列表 |
| success | function | 否               | 回调函数 |
| error   | function | 否               | 回调函数 |

**success回调函数参数**

**Object object**

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |

**object.error回调函数参数**

**Object object**

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |

### 示例

```
//示例1
syberh.runtime.launchApp({
	url:"handle:action?param1=1&param2=2",
	success: function(result){
		console.log('code: ', result.code);
		console.log('msg: ', result.msg);
	},
	error: function(error){
		console.log('code: ', error.code);
		console.log('msg: ', error.msg);
	}
});

syberh.runtime.launchApp({
	url:"handle:action?param1=1&param2=2",
}).then(function(result) {
    console.log('code: ', result.code);
	console.log('msg: ', result.msg);
}).catch(function(error) {
    console.log('code: ', error.code);
	console.log('msg: ', error.msg);
});

//示例2
var params = [];
params.push("param1=1");
params.push("param2=2");

syberh.runtime.launchApp({
	appid:"4567890",
	params:params,
	success: function(result){
		console.log('code: ', result.code);
		console.log('msg: ', result.msg);
	},
	error: function(error){
		console.log('code: ', error.code);
		console.log('msg: ', error.msg);
	}
});

syberh.runtime.launchApp({
	appid:"4567890",
	params:params
}).then(function(result) {
    console.log('code: ', result.code);
	console.log('msg: ', result.msg);
}).catch(function(error) {
    console.log('code: ', error.code);
	console.log('msg: ', error.msg);
});
```

