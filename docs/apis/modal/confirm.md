---
title: confirm
---

确认框：用于提示用户的确认框。

可以设置确认框的标题、标题图标、内容、按钮文字、按钮文字颜色是否加载图标等，仅支持成功、警告图标。

支持`Promise` 化使用。



## syber.modal.confirm(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | -------------- | ---------------------------- |
| title | string |  | 否 | 标题，最多 7 个汉字 |
| titleIcon | string |       | 否 | 标题图标 |
| content | string |  | 是 | 显示内容 |
| showCancel | boolean | true | 否 | 取消按钮显示文字信息 |
| cancelText | string  | 取消 | 否 | 取消按钮文字，最多 4 个汉字 |
| cancelColor | string | #000000 | 否 | 取消按钮文字颜色 |
| confirmText | string | 确定 | 否 | 确认按钮文字，最多 4 个汉字 |
| confirmColor | string| #576B95  | 否 | 确认按钮文字颜色 |
| showLoading | boolean |  false   | 否 | 确认按钮是否显示加载图标 |
| success | function |  |  否     | 回调成功      |
| fail   | function |  |  否     | 回调失败      |


#### object.titleIcon 的合法值
| 值     | 说明    |       
| ---------- | ------- | 
| success | 成功图标 |
| warning | 警告图标 |

#### object.success回调函数
#### 参数
true，表示用户点击了确定按钮, false，表示用户点击了取消

#### object.fail回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |


### 代码示例
```javascript
    syber.modal.confirm({
        title: '提示',
        content: '这是一个模态弹窗',
        success: function (result) {
            if (result === true) {
                console.log('用户点击了确定')
            } else if (result === false) {
                console.log('用户点击了取消')
            }
        },
        fail: function(error) {
            console.log(error.msg)
        }
    })
```

#### Promise
```javascript
    syber.modal.confirm({
        title: '提示',
        content: '这是一个模态弹窗',
    }).then(function(res) {
        if (res === true) {
            console.log('用户点击了确定')
        } else if (res === false) {
            console.log('用户点击了取消')
        }
    }).catch(function(error) {
        console.log(error.msg)
    })
```