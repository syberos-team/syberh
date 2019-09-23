---
title: cancel
---


取消上传：取消正在上传的文件。

设置文件上传id，根据文件上传id可以取消文件下载。


## syberh.upload.cancel(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| uploadID | String |  | 是 | 上传ID |
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
syberh.upload.cancel({
    'uploadID': uploadID,
    success: function (result) {
        console.log('success',result);   
    },
    fail: function (error) {
        console.log('fail: ', error);
    }
});
```
