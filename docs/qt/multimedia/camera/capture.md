---
title: 相机
---

# 概况

<span class="arg-name">camera</span> 模块管理设备的摄像头，可用于拍照、摄像操作。

摄像头资源为独占资源，如果其它程序或页面已经占用摄像头，再次操作则失败。



## openCamera

启动相机功能。可指定摄像头，默认显示主摄像头。



**参数**

| 参数名     | 类型    | 是否必填 | 描述                                      |
| ---------- | ------- | -------- | ----------------------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用              |
| camera     | long    | 是       | 指定摄像头，`1` ：主摄像头，`2`：辅摄像头 |

**示例代码**

```
void openCamera(QString callbackId,long camera)
```



## capturePhoto

进行拍照功能，成功则返回图片文件路径



**参数**

| 参数名     | 类型    | 是否必填 | 描述                                      |
| ---------- | ------- | -------- | ----------------------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用              |
| camera     | long    | 是       | 指定摄像头，`1` ：主摄像头，`2`：辅摄像头 |

**示例代码**

```
void capturePhoto(QString callbackId,long camera);
```



**成功信号**

| 参数名     | 类型     | 是否必填 | 描述                         |
| ---------- | -------- | -------- | ---------------------------- |
| responseID | long     | 是       | 回调ID，用于标识每一次的调用 |
| result     | QVariant | 是       | 返回内容                     |

result:

| 参数名 | 类型    | 是否必填 | 描述         |
| ------ | ------- | -------- | ------------ |
| path   | QString | 是       | 图片文件路径 |



**示例代码**

```
emit success(long responseID, QVariant result);
```

```
result:
{
	path: "/doc/image"	
}
```



## captureVideoStart

开始摄像功能



**参数**

| 参数名     | 类型    | 是否必填 | 描述                                      |
| ---------- | ------- | -------- | ----------------------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用              |
| camera     | long    | 是       | 指定摄像头，`1` ：主摄像头，`2`：辅摄像头 |

**示例代码**

```
void captureVideoStart(QString callbackId, long camera);
```



## captureVideoEnd

结束摄像，成功则返回视频文件路径



**参数**

| 参数名     | 类型    | 是否必填 | 描述                                      |
| ---------- | ------- | -------- | ----------------------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用              |
| camera     | long    | 是       | 指定摄像头，`1` ：主摄像头，`2`：辅摄像头 |

**示例代码**

```
void captureVideoEnd(QString callbackId,long camera);
```



**成功信号**

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | long    | 是       | 回调ID，用于标识每一次的调用 |
| result     | QString | 是       |                              |

result:

| 参数名 | 类型    | 是否必填 | 描述         |
| ------ | ------- | -------- | ------------ |
| path   | QString | 是       | 视频文件路径 |



**示例代码**

```
emit success(long responseID, QVariant result);
```

```
result:
{
	path: "/doc/video"	
}
```



## 失败信号

**参数**

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | long    | 是       | 回调ID，用于标识每一次的调用 |
| code       | long    | 是       | 错误码                       |
| msg        | QString | 是       | 错误信息                     |

**示例代码**

```
emit failed(long responseID, long code, QString msg);
```

```
{
	code: 500,
    msg: "系统错误"
}
```

