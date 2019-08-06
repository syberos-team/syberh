---
title: setItem
---

该方法可以通过键值对的形式将数据存储到本地。同时可以通过该方法，更新已有的数据。

### setItem(key, value, callback)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| key | string | 是       | 键名 |
| value | string | 是       | 键值 |
| callback | function(res) | 否       | 执行操作成功后的回调, res.result是true, 表示执行成功 |


### 代码示例
``` javascript
    syber.storage.setItem('username', 'syber', function(res) {
        console.log(res.result === true)
    })
```