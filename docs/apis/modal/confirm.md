---
title: confirm
---

确认框用于使用户可以验证或者接受某些信息。当确认框出现后，用户需要点击确定或者取消按钮才能继续进行操作, 支持`Promise` 化使用


## confirm(Object object)
### 参数
#### Object object
| 属性     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| message | string | 是 | 警告框内显示的文字信息 |
| okTitle | string | 否 | 确认按钮上显示的文字信息 |
| cancelTitle | string | 否 | 取消按钮上显示的文字信息 |
| success | function | 是       | 回调函数      |
| error   | function | 是       | 回调函数      |

#### object.success回调函数
#### 参数
#### Object res
| 属性     | 类型    | 是否必填 | 描述                            |
| ---------- | ------- | -------- | ---------------------------- |
| result | String  | 是     | 用户按下的按钮文字信息  |

#### object.error回调函数
#### 参数
#### Object error
| 属性 | 类型  | 是否必填 | 描述 |
| -- | -- | -- | -- |
| code | String  | 是 | 错误码 |
| msg | String  | 是 | 错误信息 |


### 代码示例
```javascript
    syber.modal.confirm({
        message: 'Do you confirm ?',
        okTitle: 'ok',
        cancelTitle: 'cancel',
        success: function(res) {
            console.log(res.result)
        },
        error: function(error) {
            console.log(error.msg)
        }
    })
```

#### Promise
```javascript
    syber.modal.confirm({
        message: 'Do you confirm ?',
        okTitle: 'ok',
        cancelTitle: 'cancel'
    }).then(function(res) {
        console.log(res.result)
    }).catch(function(error) {
        console.log(error.msg)
    })
```