---
title: getAllKeys
---

返回一个包含全部已存储项键名的数组。

### getAllKeys(options)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| success | function | 是       | 回调函数      |
| error   | function | 是       | 回调函数      |


#### success回调函数参数
| 参数名     | 类型    | 是否必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | result是true, 表示执行成功  |

#### error回调函数参数
| 参数名 | 类型  | 是否必填 | 描述 |
| -- | -- | -- | -- |
| code | String  | 是 | 错误码 |
| msg | String  | 是 | 错误码 |

### 代码示例
``` javascript
    syber.storage.getAllKeys({
        success: function(res) {
            console.log(res.result)
        },
        error: function(error) {
            console.log(error.msg)
        }
    })
```