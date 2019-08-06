---
title: alert
---

警告框经常用于确保用户可以得到某些信息。当警告框出现后，用户需要点击确定按钮才能继续进行操作, 支持`Promise` 化使用


## syber.modal.alert(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  是否必填 | 描述                         |
| ---------- | ------- | -------- | -------- | ---------------------------- |
| title | string |  | 否 | 警告框内显示的文字信息 |
| titleIcon | string |       | 否 | 标题左侧的图标 |
| content | string |  | 是 | 确认按钮上显示的文字信息 |
| confirmText | string | '确定' | 否 | 确认按钮的文字，最多 4 个字符 |
| confirmIcon | string |       | 否 | 确认按钮的图标 |
| confirmColor | string| '#576B95'  | 否 | 确认按钮的文字颜色，必须是 16 进制格式的颜色字符串 |
| success | function |  |  是     | 回调函数      |
| error   | function |  |  是     | 回调函数      |


#### object.error回调函数
#### 参数
#### Object err
| 属性 | 类型  | 描述 |
| -- | -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
```javascript
    syber.modal.alert({
        content: 'This is a alert'
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
        content: 'This is a alert'
    }).then(function() {

    }).catch(function(error) {
        console.log(error.msg)
    })
```
