---
title: runtime
---

# runtime

`runtime` 模块管理运行环境，可用于获取当前运行环境信息、与其它程序进行通讯等。

## launchApp(options)

一个应用希望启动另一个应用时调用

### 参数

| 参数名  | 类型     | 是否必填 | 描述     |
| ------- | -------- | -------- | -------- |
| url     | String   | 是       | app地址  |
| success | function | 否       | 回调函数 |
| error   | function | 否       | 回调函数 |

**success回调函数参数**

| 类型   | 是否必填 | 描述     |
| ------ | -------- | -------- |
| String | 否       | 成功信息 |

**error回调函数参数**

| 参数名 | 类型   | 是否必填 | 描述     |
| ------ | ------ | -------- | -------- |
| code   | String | 是       | 错误码   |
| msg    | String | 是       | 错误信息 |

### 示例

```
syber.runtime.launchApp({
	url:"handle:action?param1=1&param2=2",
	success: function(result){
		console.log('success: ', result.path);
	},
	error: function(err){
		console.log('error: ', err.code, err.msg);
	}
});
```



## launchApp(appid, params)

当一个应用希望启动本包中的另一个应用时

### 参数

| 参数名  | 类型     | 是否必填 | 描述     |
| ------- | -------- | -------- | -------- |
| appid   | String   | 是       | appid    |
| params  | Array    | 否       | 参数     |
| success | function | 否       | 回调函数 |
| error   | function | 否       | 回调函数 |

**success回调函数参数**

| 类型   | 是否必填 | 描述     |
| ------ | -------- | -------- |
| String | 否       | 成功信息 |

**error回调函数参数**

| 参数名 | 类型   | 是否必填 | 描述     |
| ------ | ------ | -------- | -------- |
| code   | String | 是       | 错误码   |
| msg    | String | 是       | 错误信息 |

### 示例

```
var params = [];
params.push("param1=1");
params.push("param2=2");
syber.runtime.launchApp({
	appid:"4567890-",
	params:params,
	success: function(result){
		console.log('success: ', result.path);
	},
	error: function(err){
		console.log('error: ', err.code, err.msg);
	}
});
```

