---
title: cancel
---

### syber.download.cancel(Object object)

> 取消下载资源

### 入参

> Object类型，属性如下：

属性 | 类型 | 必填 | 描述
---|---|---|---
downloadID | String | 是 | 下载ID
success | Function | 否 | 调用成功的回调函数
fail | Function | 否 | 调用失败的回调函数

### success 回调函数

> Object类型，属性如下：

属性 | 类型 | 描述
---|---|---|
result | Boolean | |

### 示例代码
```javascript
syber.download.cancel({
      'downloadID': downloadId,
      success: function (result) {
        console.info(result)
      },
      fail: function (error) {
        console.info(error)
      }
    });
```
