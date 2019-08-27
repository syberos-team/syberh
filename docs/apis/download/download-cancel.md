---
title: cancel
---


取消下载：用于取消正在下载的文件。

设置文件下载id，根据文件下载id可以取消文件下载。


## syber.download.cancel(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| downloadID | String |  | 是 | 下载ID |
| success | Function |  | 否 | 回调成功 |
| fail | Function |  | 否 |  回调失败 |


#### object.success回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| result | Boolean | |


#### object.fail回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 示例代码
```javascript
syber.download.cancel({
  'downloadID': downloadId,
  success: function (result) {
    console.log('success',result.path);   
  },
  fail: function (error) {
    console.log('fail: ', error.code, error.msg);
  }
});
```
