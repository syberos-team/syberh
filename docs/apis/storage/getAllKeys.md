---
title: getAllKeys
---

返回一个包含全部已存储项键名的数组。

### getAllKeys(callback)
| 参数 | 说明 | 类型 |
| --  | -- | -- |
| callback | 执行操作成功后的回调, res.result是返回的键名的数组 | function(res) |

### 代码示例
``` javascript
    syber.storage.getAllKeys(function(res) {
        console.log(res.result)
    })
```