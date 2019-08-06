---
title: 相机
---

# 概况

<span class="arg-name">camera</span> 模块管理设备的摄像头，可用于拍照、摄像操作。

摄像头资源为独占资源，如果其它程序或页面已经占用摄像头，再次操作则失败。



## openCamera

开启相机功能



### 参数

```
void openCamera(QString callbackId,int camera)
```

- callbackId：  回调ID，用于标识每一次的调用
- camera: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头



## capturePhoto

进行拍照功能



### 参数

```
void capturePhoto(QString callbackId,int camera);
```

- callbackId：  回调ID，用于标识每一次的调用

- camera: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头

  

### 信号

```
void success(long responseID, QVariant result);
```

- responseID:	回调ID，用于标识每一次的调用
- result: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头
  - path:  String 图片文件的路径



```
{
	path: "/doc/image"	
}
```



## captureVideoStart

开始摄像



### 参数

```
void success(long responseID, QVariant result);
```

- callbackId：  回调ID，用于标识每一次的调用
- camera: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头



## captureVideoEnd

结束摄像



### 参数

```
void captureVideoEnd(QString callbackId,int camera);
```

- callbackId：  回调ID，用于标识每一次的调用
- camera: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头



### 信号

```
void success(long responseID, QVariant result);
```

- responseID:	回调ID，用于标识每一次的调用

- result: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头

  - path:  String 视频文件的路径

    

```
{
	path: "/doc/video"	
}
```

## 失败信号

#### 参数

```
void failed(long responseID, QVariant long errorCode, QString errorMsg);
```

- callbackId:	回调ID，用于标识每一次的调用
- code:	错误码
- msg:	错误信息

```
{
	code: 500,
    msg: "系统错误"
}
```



