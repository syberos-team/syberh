---
title: removeItem
---

传入一个键名将会删除本地存储中对应的键值

### removeItem(key, callback)

| 参数 | 说明 | 类型 |
| -- | -- | -- |
| key | 要删除的键，不允许是 "" 或 null | string
| callback | 执行操作成功后的回调, res.result是true, 表示执行成功 | function(res) |


### 代码示例
``` javascript
    syber.storage.removeItem('username', function(res) {
        console.log(res.result)
    })
```