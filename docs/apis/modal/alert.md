---
title: alert
---

警告框经常用于确保用户可以得到某些信息。当警告框出现后，用户需要点击确定按钮才能继续进行操作。


### alert(options, callback)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| message | string | 是 | 警告框内显示的文字信息 |
| okTitle | string | 否 | 确认按钮上显示的文字信息 |
| callback | function() | 否 | 执行操作成功后的回调 |

### 代码示例
```javascript
    syber.modal.alert({
        message: 'This is a alert',
        okTitle: '确认'
    }, function () {
        console.log('alert callback')
    })
```
