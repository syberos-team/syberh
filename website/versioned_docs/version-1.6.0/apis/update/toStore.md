---
title: 去更新
id: version-1.6.0-toStore
original_id: toStore
---

## syberh.update.toStore()

> 前提：在企业商店上架，并且修改[storeBaseUrl](/docs/app-config.html)

跳转到企业商店去更新

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
  syberh.update.toStore({
    success: function() {
      console.log('success')
    },
    fail: function(error) {
      console.log('error: ', error.code, error.msg)
    }
  })
```
