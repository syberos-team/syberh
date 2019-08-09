---
title: downloadFile
---

### syber.download.downloadFile(Object object)

> 下载文件资源到本地

### 入参

> Object类型，属性如下：

属性 | 类型 | 必填 | 描述
---|---|---|---
src | String | 是 | 下载文件地址
success | Function | 否 | 调用成功的回调函数
error | Function | 否 | 调用失败的回调函数

### success 回调函数

属性 | 类型 | 描述
---|---|---
src | String |文件临时存放的位置

### 示例代码
```javascript
syber.download.downloadFile({
      src: 'http://*/TB1x669SXXXXXbdaFXXXXXXXXXX-520-280.jpg',
      success: function(res) {
        console.log(res);
      },
      error: function(res) {
        console.log(res);
      },
      complete: function(res) {
        console.log(res);
      }
    });
	
syber.download.downloadFile({
      src: 'http://*/TB1x669SXXXXXbdaFXXXXXXXXXX-520-280.jpg'
    }).then(function(res) {
		console.log(res);
	}).catch(function(res) {
		console.log(res);
	});
```
