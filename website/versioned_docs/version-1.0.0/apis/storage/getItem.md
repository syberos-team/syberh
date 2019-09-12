---
title: getItem
id: version-1.0.0-getItem
original_id: getItem
---

根据键名查询键值：传入键名返回对应的键值。

<!-- 支持`Promise` 使用。 -->

## syberh.storage.getItem(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| key | string |   | 是       | 键名 |
| success | function |  |  是       | 回调成功      |
| fail   | function |  |  是       | 回调失败     |

#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| value | string  | 是     | 存储键值 |

#### object.fail 回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |


### 代码示例
``` javascript
syberh.storage.getItem({
    key: 'name',
    success: function(result) {
        console.log('success',result); 
    },
    fail: function(error) {
        console.log('fail: ', error.code, error.msg);
    }
})
```

<!-- #### Promise
``` javascript
syberh.storage.getItem({
    key: 'name'
}).then(function(result) {
    console.log('success',result); 
}).catch(function(error) {
    console.log('fail: ', error.code, error.msg);
})
``` -->