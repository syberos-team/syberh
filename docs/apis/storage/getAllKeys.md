---
title: getAllKeys
---

返回一个包含全部已存储项键名的数组。

### getAllKeys(callback)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callback | function(res) | 是 | 执行操作成功后的回调, res.result是true, 表示执行成功 |

### 代码示例
``` javascript
    syber.storage.getAllKeys(function(res) {
        console.log(res.result)
    })
```