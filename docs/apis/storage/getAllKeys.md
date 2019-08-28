---
title: getAllKeys
---

查询所有数字：返回一个包含全部已存储项键名的数组。

支持`Promise` 使用。

## syber.storage.getAllKeys(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| success | function |  |  是       | 回调成功      |
| fail   | function |  |  是       | 回调失败      |


#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| keys | array | 是     | 存储键名的数组 |

#### object.fail 回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
``` javascript
syber.storage.getAllKeys({
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
syber.storage.getAllKeys()
    .then(function(result) {
        console.log('success',result); 
    }).catch(function(error) {
        console.log('fail: ', error.code, error.msg);
    })
```