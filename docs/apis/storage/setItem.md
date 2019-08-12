---
title: setItem
---

该方法可以通过键值对的形式将数据存储到本地。同时可以通过该方法，更新已有的数据, 支持`Promise` 化使用

## syber.storage.setItem(Object object)
### 参数
#### Object object
| 属性     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| key | string | 是       | 键名 |
| value | string | 是       | 键值 |
| success | function | 是       | 回调函数      |
| fail   | function | 是       | 回调函数      |

#### object.success 回调函数参数
#### 参数
#### Object res
| 属性     | 类型    | 是否必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| res | boolean  | 是     | 返回true, 表示执行成功  |

#### object.fail 回调函数
#### 参数
#### Object res
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |


### 代码示例
``` javascript
    syber.storage.setItem({
        key: 'name',
        value: 'syber',
        success: function(res) {
            console.log(res)
        },
        fail: function(res) {
            console.log(res.msg)
        }
    })
```

#### Promise
``` javascript
    syber.storage.setItem({
        key: 'name'
    }).then(function(res) {
        console.log(res)
    }).catch(function(res) {
        console.log(res.msg)
    })
```