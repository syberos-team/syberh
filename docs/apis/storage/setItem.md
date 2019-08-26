---
title: setItem
---

可以通过键值对的形式将数据存储到本地。同时可以通过该方法，更新已有的数据。

支持`Promise` 使用。

## syber.storage.setItem(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| key | string |  | 是       | 键名 |
| value | string |  |  是       | 键值 |
| success | function |  |  是       | 回调成功      |
| fail   | function |   | 是       | 回调失败      |

#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 是否必填 | 描述                     |
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
    syber.storage.setItem({
        key: 'name',
        value: 'syber',
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
    syber.storage.setItem({
        key: 'name'
    }).then(function(result) {
    console.log('success',result); 
    }).catch(function(error) {
        console.log('fail: ', error.code, error.msg);
    })
```