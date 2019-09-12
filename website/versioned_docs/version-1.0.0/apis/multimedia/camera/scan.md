---
title: scan
id: version-1.0.0-scan
original_id: scan
---

`barcode` 模块管理条码扫描识别，目前仅支持二维码（QR）。

通过调用摄像头对条码进行扫描识别，扫描到条码后进行解码并返回码数据内容。



## syberh.barcode.scan（Object object）

扫描二维码，成功则返回条码内容



### 参数

#### Object object

| 属性    | 类型     | 是否必填 | 描述                                      |
| ------- | -------- | -------- | ----------------------------------------- |
| success | function | 否       | 接口调用成功的回调函数                    |
| fail   | function | 否       | 接口调用失败的回调函数                    |

**object.success回调参数**

| 参数名  | 类型   | 描述         |
| ------- | ------ | ------------ |
| content | String | 二维码的内容 |

**object.fail 回调参数**

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### 示例代码

```
syberh.barcode.scan({
	success: function(result){
		console.log('success: ', result.content);
	},
	error: function(err){
		console.log('error: ', err.code, err.msg);
	}
});
```

