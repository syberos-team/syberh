## 下载文件
> 下载文件资源到本地

### syber.downloadFile
#### 入参

属性 | 类型 | 必填 | 描述
---|---|---|---
src | String | 是 | 下载文件地址
success | Function | 否 | 调用成功的回调函数
fail | Function | 否 | 调用失败的回调函数
complete | Function | 否 | 调用结束的回调函数（调用成功、失败都会执行）

#### success 回调函数

名称 | 类型 | 描述
---|---|---
src | String |文件临时存放的位置

#### 示例代码
```javascript
syber.downloadFile({
      src: 'http://*/TB1x669SXXXXXbdaFXXXXXXXXXX-520-280.jpg',
      success: function(res) {
        console.log(res);
      },
      fail: function(res) {
        console.log(res);
      },
      complete: function(res) {
        console.log(res);
      }
    });
```
### DownloadTask
> 一个可以监听下载进度变化事件，以及取消下载任务的对象

#### 取消下载文件
```javascript
DownloadTask.abort()
```
#### 监听下载进度变化事件
#### 入参
```javascript
DownloadTask.progress()
```
属性 | 类型 | 必填 | 描述
---|---|---|---
callback | Function | 是 | 下载进度变化事件的回调函数

#### 回调函数
> 入参为 Object 类型，属性如下：

属性 | 类型 | 描述
---|---|---
progress | number | 下载进度百分比
totalBytesWritten | number | 已经下载的数据长度，单位 Bytes
totalBytesExpectedToWrite | number | 预期需要下载的数据总长度，单位 Bytes


### syber.getFileInfos
> 获取文件信息

#### 入参

属性 | 类型 | 必填 | 描述
---|---|---|---
src | String | 是 | 图片的路径，可以是相对路径、临时文件路径、存储文件路径、网络图片路径
success | Function | 否 | 调用成功的回调函数
fail | Function | 否 | 调用失败的回调函数
complete | Function | 否 | 调用结束的回调函数（调用成功、失败都会执行）

#### success 回调函数
> 入参为 Object 类型，属性如下：

属性 | 类型 | 描述
---|---|---
width | number | 图片原始宽度，单位px。不考虑旋转
height | number | 图片原始高度，单位px。不考虑旋转
type | string | 图片格式
size | number | 文件大小

#### 示例代码
```javascript
syber.getFileInfos({
      src: 'http://*/TB1x669SXXXXXbdaFXXXXXXXXXX-520-280.jpg',
      success: function(res) {
        console.log(res);
      },
      fail: function(res) {
        console.log(res);
      },
      complete: function(res) {
        console.log(res);
      }
    });
```

### syber.removeFileInfos
> 删除某个保存的文件

#### 入参

属性 | 类型 | 必填 | 描述
---|---|---|---
src | String | 是 | 图片的路径，可以是相对路径、临时文件路径、存储文件路径、网络图片路径
success | Function | 否 | 调用成功的回调函数
fail | Function | 否 | 调用失败的回调函数
complete | Function | 否 | 调用结束的回调函数（调用成功、失败都会执行）

#### 示例代码
```javascript
syber.removeFileInfos({
      src: 'http://*/TB1x669SXXXXXbdaFXXXXXXXXXX-520-280.jpg',
      success: function(res) {
        console.log(res);
      },
      fail: function(res) {
        console.log(res);
      },
      complete: function(res) {
        console.log(res);
      }
    });
```

