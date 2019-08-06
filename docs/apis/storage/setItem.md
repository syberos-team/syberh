---
title: setItem
---

该方法可以通过键值对的形式将数据存储到本地。同时可以通过该方法，更新已有的数据。

### setItem(key, value, callback)

| 参数 | 说明 | 类型 |
| -- | -- | -- |
| key | 要存储的键，不允许是 "" 或 null | string  |
| value | 要存储的值，不允许是 "" 或 null | string |
| callback | 执行操作成功后的回调, res.result是true, 表示执行成功 | function(res) |


### 代码示例
``` javascript
    syber.storage.getAllKeys('username', 'syber', function(res) {
        console.log(res.result === true)
    })
```