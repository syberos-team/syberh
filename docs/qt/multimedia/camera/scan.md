---
title: 扫码
---

# 概况

<span class="arg-name">barcode</span> 模块管理条码（一维码和二维码）扫描识别，目前仅支持二维码（QR）。
通过调用摄像头对条码进行扫描识别，扫描到条码后进行解码并返回码数据内容及码类型。



## scan

开启摄像头扫描二维码

### 参数

```
QJsonObject scan(QString callbackId,int camera);
```

- callbackId：  回调ID，用于标识每一次的调用
- camera: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头



### 成功信号

```
void success(long responseID, QVariant result);
```

- responseID:	回调ID，用于标识每一次的调用

- result: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头

  - type:  String 二维码的类型
  - content: String 二维码的内容

  

```
{
	type: "/doc/video",
    content: "二维码内容"
}
```


### 失败信号


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

