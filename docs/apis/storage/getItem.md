---
title: getItem
---

传入键名返回对应的键值。

### getItem(key, callback)

| 参数 | 说明 | 类型 |
| --  | -- | -- |
| key | 要存储的键，不允许是 "" 或 null | string
| callback | 执行操作成功后的回调, res.result是返回的键值 | function(res) |


### 代码示例
``` javascript
    syber.storage.getItem('username', function(res) {
        console.log(res.result)
    })
```