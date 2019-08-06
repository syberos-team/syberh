---
title: removeItem
---

传入一个键名将会删除本地存储中对应的键值

### removeItem(key, callback)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| key | string | 是       | 键名 |
| callback | function(res) | 否       | 执行操作成功后的回调, res.result是true, 表示执行成功 |


### 代码示例
``` javascript
    syber.storage.removeItem('username', function(res) {
        console.log(res.result)
    })
```