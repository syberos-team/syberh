---
title: getItem
---

传入键名返回对应的键值。

### getItem(key, callback)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| key | string | 是       | 键名 |
| callback | function(res) | 是       | 执行操作成功后的回调, res.result是true, 表示执行成功 |


### 代码示例
``` javascript
    syber.storage.getItem('username', function(res) {
        console.log(res.result)
    })
```