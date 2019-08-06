---
title: confirm
---

确认框用于使用户可以验证或者接受某些信息。当确认框出现后，用户需要点击确定或者取消按钮才能继续进行操作。


### confirm(options, callback)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| message | string | 是 | 警告框内显示的文字信息 |
| okTitle | string | 否 | 确认按钮上显示的文字信息 |
| cancelTitle | string | 否 | 取消按钮上显示的文字信息 |
| callback | function(res) | 是 | 执行操作成功后的回调, res.result是用户按下的按钮文字信息 |

### 代码示例
```javascript
    syber.modal.confirm({
        message: 'Do you confirm ?',
        okTitle: 'ok',
        cancelTitle: 'cancel',
    }, function (data) {
        console.log(data.result)
    })
```