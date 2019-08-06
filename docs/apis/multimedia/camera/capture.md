---
title: 相机
---

# 概况

<span class="arg-name">camera</span> 模块管理设备的摄像头，可用于拍照、摄像操作。

摄像头资源为独占资源，如果其它程序或页面已经占用摄像头，再次操作则失败。



## openCamera

开启相机功能



### 参数

- camera: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头



### 示例

```
syber.camera.openCamera({
	camera: '1'
});
```



## capturePhoto

进行拍照功能



### 参数

- camera: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头
- success:  function(result) 拍照操作完成时调用，用于返回图片文件的路径
  - result: Object 图片信息
    - path:  String 图片文件的路径
- error:  function(err) 失败时的回调
  - err:  Object 错误信息
    - code:  String 错误码
    - msg:  String 错误消息



### 示例

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

开始摄像



### 参数

- camera: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头



### 示例

```
syber.camera.captureVideoStart({
	camera: '1'
});
```



## captureVideoEnd

结束摄像



### 参数

- camera: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头
- success:  function(result) 结束摄像操作完成时调用，用于返回视频文件的路径
  - result: Object 视频信息
    - path:  String 视频文件的路径
- error:  function(err) 失败时的回调
  - err:  Object 错误信息
    - code:  String 错误码
    - msg:  String 错误消息



### 示例

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

