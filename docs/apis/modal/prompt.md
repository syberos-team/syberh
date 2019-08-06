---
title: prompt
---

提示框经常用于提示用户在进入页面前输入某个值。当提示框出现后，用户需要输入某个值，然后点击确认或取消按钮才能继续操作, 支持`Promise` 化使用


## prompt(Object object)
### 参数
#### Object object
| 属性     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| message | string | 是 | 警告框内显示的文字信息 |
| okTitle | string | 否 | 确认按钮上显示的文字信息 |
| cancelTitle | string | 否 | 取消按钮上显示的文字信息 |
| success | function | 是       | 回调函数      |
| error   | function | 是       | 回调函数      |


#### object.success回调函数参数
#### 参数
#### Object res
| 属性     | 类型    | 是否必填 | 描述                            |
| ---------- | ------- | -------- | ---------------------------- |
| result | String  | 是     | 用户按下的按钮文字信息  |
| data | String  | 是     | 用户输入的文字信息  |

#### object.error回调函数
#### 参数
#### Object error
| 属性 | 类型  | 是否必填 | 描述 |
| -- | -- | -- | -- |
| code | String  | 是 | 错误码 |
| msg | String  | 是 | 错误信息 |

### 代码示例
```javascript
    syber.modal.prompt({
        message: 'This is a prompt',
        duration: 0.3,
        success: function(res) {
            console.log(res.result)
        },
        error: function(error) {
            console.log(error.msg)
        }
    })
```

```javascript
    syber.modal.prompt({
        message: 'This is a prompt',
        duration: 0.3
    }).then(function(res) {
        console.log(res.result)
    }).catch(function(error) {
        console.log(error.msg)
    })
```