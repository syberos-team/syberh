---
title: captureVideoEnd
id: version-1.1.0-captureVideoEnd
original_id: captureVideoEnd
---


## syberh.camera.captureVideoEnd（Object object）

结束摄像，成功则返回视频文件路径



### **参数**

**Object object**

| 属性    | 类型     | 是否必填 | 描述                                      |
| ------- | -------- | -------- | ----------------------------------------- |
| camera  | number   | 是        | 指定摄像头，`1` ：主摄像头，`2`：辅摄像头 |
| success | function | 否       | 接口调用成功的回调函数                    |
| error   | function | 否       | 接口调用失败的回调函数                    |

**object.success回调参数**

| 属性 | 类型   | 描述         |
| ---- | ------ | ------------ |
| path | String | 视频文件路径 |

**object.error回调参数**

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **示例代码**

```
syberh.camera.captureVideoEnd({
	camera: '1',
	success: function(result){
		console.log('success: ', result.path);
	},
	error: function(err){
		console.log('error: ', err.code, err.msg);
	}
});
```


