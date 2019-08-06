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

名称 | 类型 | 描述
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
### DownloadTask
> 一个可以监听下载进度变化事件，以及取消下载任务的对象

### 取消下载文件
```javascript
DownloadTask.abort()
```
### 监听下载进度变化事件
### 入参
```javascript
DownloadTask.progress(Object object)
```
属性 | 类型 | 必填 | 描述
---|---|---|---
callback | Function | 是 | 下载进度变化事件的回调函数

### 回调函数
> 入参为 Object 类型，属性如下：

属性 | 类型 | 描述
---|---|---
progress | number | 下载进度百分比
totalBytesWritten | number | 已经下载的数据长度，单位Bytes
totalBytesExpectedToWrite | number | 预期需要下载的数据总长度，单位Bytes
