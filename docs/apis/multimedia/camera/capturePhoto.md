---
title: takePictureImmediately
---




## syber.camera.takePictureImmediately()

进行拍照功能，成功则返回图片路径



### **参数**

**Object object**

| 属性    | 类型     | 是否必填 | 描述                                      |
| ------- | -------- | -------- | ----------------------------------------- |
| success | function | 否       | 接口调用成功的回调函数                    |
| fail   | function | 否       | 接口调用失败的回调函数                    |

**object.success回调参数**

| 属性 | 类型   | 描述         |
| ---- | ------ | ------------ |
| path | String | 图片文件路径 |

**object.fail回调参数**

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **示例代码**

```
syber.camera.takePictureImmediately({
	success: function(result){
		console.log('success: ', result.path);
	},
	fail: function(err){
		console.log('fail: ', err.code, err.msg);
	}
});
```

