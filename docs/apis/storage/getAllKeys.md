---
title: getAllKeys
---

返回一个包含全部已存储项键名的数组, 支持`Promise` 化使用

## syber.storage.getAllKeys(Object object)
### 参数
#### Object object
| 属性     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| success | function | 是       | 回调函数      |
| fail   | function | 是       | 回调函数      |


#### object.success 回调函数参数
#### 参数
#### Object res
| 属性     | 类型    | 是否必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| keys | array | 是     | 已存储的键名的数组 |

#### object.fail 回调函数
#### 参数
#### Object res
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
``` javascript
    syber.storage.getAllKeys({
        success: function(res) {
            console.log(res.keys)
        },
        fail: function(res) {
            console.log(res.msg)
        }
    })
```

#### Promise
``` javascript
    syber.storage.getAllKeys()
        .then(function(res) {
            console.log(res)
        }).catch(function(res) {
            console.log(res.msg)
        })
```