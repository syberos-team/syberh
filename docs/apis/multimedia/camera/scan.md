---
title: 扫码
---

# 概况

<span class="arg-name">barcode</span> 模块管理条码（一维码和二维码）扫描识别，目前仅支持二维码（QR）。

通过调用摄像头对条码进行扫描识别，扫描到条码后进行解码并返回码数据内容及码类型。



## scan

扫描二维码，成功则返回条码类型及内容



**参数**

| 参数名 | 类型 | 是否必填 | 描述                                      |
| ------ | ---- | -------- | ----------------------------------------- |
| camera | long | 1        | 指定摄像头，`1` ：主摄像头，`2`：辅摄像头 |

**success回调参数**

| 参数名  | 类型   | 描述         |
| ------- | ------ | ------------ |
| type    | String | 二维码的类型 |
| content | String | 二维码的内容 |

**error回调参数**

| 参数名 | 类型   | 描述     |
| ------ | ------ | -------- |
| code   | String | 错误码   |
| msg    | String | 错误消息 |



**示例代码**

```
syber.barcode.scan({
	camera: '1',
	success: function(result){
		console.log('success: ', result.type, result.content);
	},
	error: function(err){
		console.log('error: ', err.code, err.msg);
	}
});
```

