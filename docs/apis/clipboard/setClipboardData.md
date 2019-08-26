---
title: setClipboardData
---

向系统剪贴板设置内容,支持 `promise`调用。

支持`Promise` 使用。


## syber.clipboard.setClipboardData(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| data    | String   |  | 是       | 剪贴板的内容           |
| success | function |  |  是       | 回调成功      |
| fail   | function |  |  是       | 回调失败      |

### 示例
```javascript
  syber.clipboard.setClipboardData({
    data:"some of the content setClipboardData",
    success: function(result) {
        console.log('success: ', result.data);
    },
    error: function(error) {
      console.log('fail: ', error.code, error.msg);
    }
  }); 
```

#### Promise
``` javascript
  syber.clipboard.setClipboardData()
    .then(function(result) {
        console.log('success',result); 
    }).catch(function(error) {
        console.log('fail: ', error.code, error.msg);
    })
```
