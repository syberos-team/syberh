---
title: 扫码
---

# 概况

<span class="arg-name">barcode</span> 模块管理条码（一维码和二维码）扫描识别，目前仅支持二维码（QR）。

通过调用摄像头对条码进行扫描识别，扫描到条码后进行解码并返回码数据内容及码类型。



## scan

扫码（scan）识别图片中的条码

### 参数

- camera: String 指定要获取摄像头，默认使用主摄像头，`1` 表示主摄像头，`2` 表示辅摄像头
- success:  function(result) 扫码操作完成时调用，用于返回扫码内容
  - result: Object 扫码内容
    - path:  String 二维码的类型
    - content: String 二维码的内容
- error:  function(err) 失败时的回调
  - err:  Object 错误信息
    - code:  String 错误码
    - msg:  String 错误消息





### 示例

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

