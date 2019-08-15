---
title: prompt
---

提示框经常用于提示用户在进入页面前输入某个值。当提示框出现后，用户需要输入某个值，然后点击确认或取消按钮才能继续操作, 支持`Promise` 化使用


## syber.modal.prompt(Object object)
### 参数
#### Object object
| 属性     | 类型    | 默认值 | 必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- | ---- |
| title | string |  |否 | 确认按钮上显示的文字信息 |
| titleIcon | string |       | 否 | 标题左侧的图标 |
| content | string |  |是 | 警告框内显示的文字信息 |
| confirmText | string | '确定' | 否 | 确认按钮的文字，最多 4 个字符 |
| showLoading | boolean |  false | 否 | 确认按钮是否显示加载图标 |
| confirmColor | string| '#007aff'  | 否 | 确认按钮的文字颜色，必须是 16 进制格式的颜色字符串 |
| cancelTitle | string |  '取消' |否 | 取消按钮上显示的文字信息 |
| cancelColor | string | '#333333' | 否 | 取消按钮的文字颜色，必须是 16 进制格式的颜色字符串 |
| success | function |  |  是     | 接口调用成功的回调函数      |
| fail   | function |  |  是     | 接口调用失败的回调函数      |


#### object.titleIcon 的合法值
| 值     | 说明    |       
| ---------- | ------- | 
| success | 显示成功图标，此时 title 文本最多显示 7 个汉字长度 |
| warning | 显示警告图标，此时 title 文本最多显示 7 个汉字长度 |


#### object.success回调函数参数
#### 参数
#### Object res
| 属性     | 类型    | 描述                            |
| ---------- | ------- | ---------------------------- |
| confirm | boolean  | 为 true 时，表示用户点击了确定按钮 |
| cancel | boolean  | 为 true 时，表示用户点击了取消  |
| data | String   | 用户输入的文字信息  |

#### object.fail回调函数
#### 参数
#### Object error
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
```javascript
    syber.modal.prompt({
        content: 'This is a prompt',
        success: function(res) {
            console.log(res.result)
        },
        fail: function(error) {
            console.log(error.msg)
        }
    })
```

#### Promise
```javascript
    syber.modal.prompt({
        content: 'This is a prompt',
    }).then(function(res) {
        console.log(res.result)
    }).catch(function(error) {
        console.log(error.msg)
    })
```