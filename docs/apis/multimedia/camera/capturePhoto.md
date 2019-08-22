---
title: takePictureImmediately
---




## syber.camera.takePictureImmediately(Object object)

进行拍照功能，可对照片进行剪裁，成功则返回图片路径



### **参数**

**Object object**

| 属性    | 类型     | 是否必填 | 描述                                      |
| ------- | -------- | -------- | ----------------------------------------- |
| enableCut | boolean | 是       | 是否启动裁剪                           |
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



### **照片示例代码**

```
syber.camera.takePictureImmediately({
	data:{enableCut:false},
	success: function(result){
		console.log('success: ', result.path);
	},
	fail: function(err){
		console.log('fail: ', err.code, err.msg);
	}
});
```

### **拍照剪裁示例代码**

```
syber.camera.takePictureImmediately({
	data:{enableCut:true},
	success: function(result){
		console.log('success: ', result.path);
	},
	fail: function(err){
		console.log('fail: ', err.code, err.msg);
	}
});
```
