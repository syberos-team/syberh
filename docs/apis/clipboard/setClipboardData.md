---
title: setClipboardData
---

## syber.clipboard.setClipboardData(Object object)
向系统剪贴板设置内容,支持 `promise`调用。

### 参数

**Object object**

| 属性    | 类型     | 是否必填 | 描述                   |
| ------- | -------- | -------- | ---------------------- |
| data    | String   | 是       | 剪贴板的内容           |
| success | function | 否       | 接口调用成功的回调函数 |
| fail    | function | 否       | 接口调用失败的回调函数 |

### 示例
```javascript
syber.clipboard.setClipboardData({
    data:"some of the content",
    success (res) {
    syber.clipboard.getClipboardData({
      success (res) {
        console.log(res.data) // data
      }
    })
  }
});

//promise 示例

syber.clipboard.setClipboardData({data:'data'}).then(function(result) {
    console.log('content: ', result.data);
     syber.clipboard.getClipboardData().then(function(res){
       console.log(res.data)
     })
}).catch(function(error) {
    console.log('code: ', error.code);
    console.log('msg: ', error.msg);
});


```
