---
title: alert
---

警告框经常用于确保用户可以得到某些信息。当警告框出现后，用户需要点击确定按钮才能继续进行操作, 支持`Promise` 化使用


## alert(Object object)
### 参数
#### Object object
| 属性     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| message | string | 是 | 警告框内显示的文字信息 |
| okTitle | string | 否 | 确认按钮上显示的文字信息 |
| success | function | 否       | 回调函数      |
| error   | function | 否       | 回调函数      |


#### object.error回调函数
#### 参数
#### Object err
| 属性 | 类型  | 是否必填 | 描述 |
| -- | -- | -- | -- |
| code | String  | 是 | 错误码 |
| msg | String  | 是 | 错误信息 |

### 代码示例
```javascript
    syber.modal.alert({
        message: 'This is a alert',
        okTitle: '确认',
        success: function() {
            
        },
        error: function(error) {
            console.log(error.msg)
        }
    })
```

#### Promise
```javascript
    syber.modal.alert({
        message: 'This is a alert',
        okTitle: '确认'
    }).then(function() {

    }).catch(function(error) {
        console.log(error.msg)
    })
```
