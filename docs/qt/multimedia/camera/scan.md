---
title: 扫码
---

# 概况

<span class="arg-name">barcode</span> 模块管理条码（一维码和二维码）扫描识别，目前仅支持二维码（QR）。
通过调用摄像头对条码进行扫描识别，扫描到条码后进行解码并返回码数据内容及码类型。



## scan

开启摄像头扫描二维码




**参数**

| PropertyType | Type    | Default | Description                               |
| ------------ | ------- | ------- | ----------------------------------------- |
| callbackId   | QString |         | 回调ID，用于标识每一次的调用              |
| camera       | long    | 1       | 指定摄像头，`1` ：主摄像头，`2`：辅摄像头 |

**示例代码**

```
void scan(QString callbackId,long camera);
```



### 成功信号

**参数**

| PropertyType | Type    | Default | Description                  |
| ------------ | ------- | ------- | ---------------------------- |
| responseID   | long    |         | 回调ID，用于标识每一次的调用 |
| result       | QString |         |                              |
| type         | QString |         | 二维码的类型                 |
| content      | QString |         | 二维码的内容                 |

**示例代码**

```
void success(long responseID, QVariant result);
```

```
{
	type: "/doc/video",
    content: "二维码内容"
}
```




### 失败信号

**参数**

| PropertyType | Type    | Default | Description                  |
| ------------ | ------- | ------- | ---------------------------- |
| responseID   | long    |         | 回调ID，用于标识每一次的调用 |
| code         | long    |         | 错误码                       |
| msg          | QString |         | 错误信息                     |

**示例代码**

```
void failed(long responseID, long code, QString msg);
```

```
{
	code: 500,
    msg: "系统错误"
}
```



