---
title: getFileInfos
id: version-1.0.0-getFileInfos
original_id: getFileInfos
---

### syberh.fileinfos.getFileInfos(Object object)

> 获取文件信息

### 入参

> Object类型，属性如下：

属性 | 类型 | 必填 | 描述
---|---|---|---
src | String | 是 | 图片的路径，可以是相对路径、临时文件路径、存储文件路径、网络图片路径
success | Function | 否 | 调用成功的回调函数
error | Function | 否 | 调用失败的回调函数

### success 回调函数
> Object类型，属性如下：

属性 | 类型 | 描述
---|---|---
width | number | 图片原始宽度，单位px。不考虑旋转
height | number | 图片原始高度，单位px。不考虑旋转
type | string | 图片格式
size | number | 文件大小

### 示例代码
```javascript
syberh.fileinfos.getFileInfos({
      src: 'http://*/TB1x669SXXXXXbdaFXXXXXXXXXX-520-280.jpg',
      success: function(res) {
        console.log(res);
      },
      error: function(res) {
        console.log(res);
      }});
	  
syberh.fileinfos.getFileInfos({
      src: 'http://*/TB1x669SXXXXXbdaFXXXXXXXXXX-520-280.jpg'
	}).then(function(res) {
		console.log(res);
	}).catch(function(res) {
		console.log(res);
	});
	
```