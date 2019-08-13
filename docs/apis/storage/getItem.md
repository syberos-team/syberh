---
title: getItem
---

传入键名返回对应的键值, 支持`Promise` 化使用

## syber.storage.getItem(Object object)
### 参数
#### Object object
| 属性     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| key | string | 是       | 键名 |
| success | function | 是       | 回调函数      |
| fail   | function | 是       | 回调函数      |

#### object.success 回调函数参数
#### 参数
#### Object res
| 属性     | 类型    | 是否必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| value | string  | 是     | 已存储的键值 |

#### object.fail 回调函数
#### 参数
#### Object res
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |


### 代码示例
``` javascript
    syber.storage.getItem({
        key: 'name',
        success: function(res) {
            console.log(res.value)
        },
        fail: function(res) {
            console.log(res.msg)
        }
    })
```

#### Promise
``` javascript
    syber.storage.getItem({
        key: 'name'
    }).then(function(res) {
        console.log(res)
    }).catch(function(res) {
        console.log(res.msg)
    })
```