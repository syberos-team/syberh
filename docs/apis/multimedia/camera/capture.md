---
title: 相机
---

# 概况

<span class="arg-name">camera</span> 模块管理设备的摄像头，可用于拍照、摄像操作。

摄像头资源为独占资源，如果其它程序或页面已经占用摄像头，再次操作则失败。



## openCamera

启动相机功能。可指定摄像头，默认显示主摄像头。



**参数**

| 参数名 | 类型 | 是否必填 | 描述                                      |
| ------ | ---- | -------- | ----------------------------------------- |
| camera | long | 是       | 指定摄像头，`1` ：主摄像头，`2`：辅摄像头 |

**示例代码**

```
syber.camera.openCamera({
	camera: '1'
});
```



## capturePhoto

进行拍照功能，成功则返回图片文件路径



**参数**

| 参数名 | 类型 | 是否必填 | 描述                                      |
| ------ | ---- | -------- | ----------------------------------------- |
| camera | long | 是       | 指定摄像头，`1` ：主摄像头，`2`：辅摄像头 |

**success回调参数**

| 参数名 | 类型   | 描述         |
| ------ | ------ | ------------ |
| path   | String | 图片文件路径 |

**error回调参数**

| 参数名 | 类型   | 描述     |
| ------ | ------ | -------- |
| code   | String | 错误码   |
| msg    | String | 错误消息 |



**示例代码**

```
syber.camera.capturePhoto({
	camera: '1',
	success: function(result){
		console.log('success: ', result.path);
	},
	error: function(err){
		console.log('error: ', err.code, err.msg);
	}
});
```



## captureVideoStart

开始摄像功能



**参数**

| 参数名 | 类型 | 是否必填 | 描述                                      |
| ------ | ---- | -------- | ----------------------------------------- |
| camera | long | 1        | 指定摄像头，`1` ：主摄像头，`2`：辅摄像头 |



**示例代码**

```
syber.camera.captureVideoStart({
	camera: '1'
});
```



## captureVideoEnd

结束摄像，成功则返回视频文件路径



**参数**

| 参数名 | 类型 | 是否必填 | 描述                                      |
| ------ | ---- | -------- | ----------------------------------------- |
| camera | long | 1        | 指定摄像头，`1` ：主摄像头，`2`：辅摄像头 |

**success回调参数**

| 参数名 | 类型   | 描述         |
| ------ | ------ | ------------ |
| path   | String | 视频文件路径 |

**error回调参数**

| 参数名 | 类型   | 描述     |
| ------ | ------ | -------- |
| code   | String | 错误码   |
| msg    | String | 错误消息 |



**示例代码**

```
syber.camera.captureVideoEnd({
	camera: '1',
	success: function(result){
		console.log('success: ', result.path);
	},
	error: function(err){
		console.log('error: ', err.code, err.msg);
	}
});
```

