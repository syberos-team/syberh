---
title: takePhoto
id: version-1.1.1-alpha.3-takePhoto
original_id: takePhoto
---


拍照：拍摄照片。

可以对拍摄后的照片进行裁剪，拍摄成功则返回图片路径。

> takePhoto 为syberos中自带的拍照功能

> 拍照功能属于敏感权限,调用摄像头必须获取相机和数据存储权限,在sopconfig.xml文件中添加如下字段:

``` javascript
<uses-permission syberos:name="syberos.permission.ACCESS_CAMERA"/>
<uses-permission syberos:name="syberos.permission.ACCESS_STORAGE"/>
```

## syberh.camera.takePhoto(Object object)
### **参数**
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| enableCut | boolean | false       | 否       | 是否启动裁剪                           |
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

**object.success回调函数**
#### 参数
| 属性 | 类型   | 描述         |
| ---- | ------ | ------------ |
| path | String | 图片路径 |

**object.fail回调函数**
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **拍照代码示例**
``` javascript
syberh.camera.takePhoto({
	success: function(result){
		console.log('success: ', result.path);
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```

### **拍照裁剪代码示例**
``` javascript
syberh.camera.takePhoto({
	enableCut:true,
	success: function(result){
		console.log('success: ', result.path);
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
