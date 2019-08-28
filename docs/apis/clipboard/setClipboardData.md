---
title: setClipboardData
---

设置剪贴板内容,支持 `promise`调用。

支持`Promise` 使用。


## syber.clipboard.setClipboardData(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| data    | String   |  | 是       | 内容           |
| success | function |  |  是       | 回调成功      |
| fail   | function |  |  是       | 回调失败      |


**object.success回调函数**
#### 参数
| 属性 | 类型   | 描述         |
| ---- | ------ | ------------ |
| data | String | 内容 |

**object.fail回调函数**
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |


### 示例
``` javascript
syber.clipboard.setClipboardData({
    data:"some of the content setClipboardData",
    success: function(result) {
        console.log('success: ', result.data);
    },
    fail: function(error) {
        console.log('fail: ', error.code, error.msg);
    }
}); 
```

#### Promise
``` javascript
syber.clipboard.setClipboardData({
    data:"some of the content setClipboardData",
}).then(function(result) {
    console.log('success: ', result.data);
}).catch(function(error) {
    console.log('fail: ', error.code, error.msg);
})
```
