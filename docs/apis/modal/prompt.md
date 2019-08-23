---
title: prompt
---

提示框经常用于提示用户在进入页面前输入某个值。当提示框出现后，用户需要输入某个值，然后点击确认或取消按钮才能继续操作, 支持`Promise` 化使用


## syber.modal.prompt(Object object)
### 参数
#### Object object
| 属性     | 类型    | 默认值 | 必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- | ---- |
| title | string |  |否 | 标题，最多7个汉字       |
| confirmText | string | '确定' | 否 | 确认按钮的文字，最多4个汉字 |
| cancelText | string |  '取消' |否 | 取消按钮的文字，最多4个汉字 |
| success | function |  |  是     | 回调成功      |
| fail   | function |  |  是     | 回调失败      |


#### object.success回调函数参数
#### 参数
#### String result
用户输入的内容, 为""时，表示用户未输入

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
        success: function(result) {
            if (result !== '') {
              console.log('用户输入的值 =》', result)
            }
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
    }).then(function(result) {
        if (result !== '') {
            console.log('用户输入的值 =》', result)
        }
    }).catch(function(error) {
        console.log(error.msg)
    })
```

#### 原生prompt调用
```javascript
    var result = prompt('哈哈哈', 'placeholder')
    if (result !== '') {
        console.log('用户输入的值 =》', result)
    }
```