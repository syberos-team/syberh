---
title: removeItem
---

传入一个键名将会删除本地存储中对应的键值。

支持`Promise` 使用。

## syber.storage.removeItem(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| key | string |   | 是       | 键名 |
| success | function |  |  是       | 回调成功      |
| fail   | function |   | 是       | 回调失败      |

#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | 返回true, 表示执行成功  |

#### object.fail 回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |


### 代码示例
``` javascript
syber.storage.removeItem({
    key: 'name',
    success: function(result) {
        console.log('success',result); 
    },
    fail: function(error) {
        console.log('fail: ', error.code, error.msg);
    }
})
```

#### Promise
``` javascript
syber.storage.removeItem({
    key: 'name'
}).then(function(result) {
console.log('success',result); 
}).catch(function(error) {
        console.log('fail: ', error.code, error.msg);
})
```