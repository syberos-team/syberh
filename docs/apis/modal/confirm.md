---
title: confirm
---

确认框用于使用户可以验证或者接受某些信息。当确认框出现后，用户需要点击确定或者取消按钮才能继续进行操作。


### confirm(options, callback)

- @options
    + <code><font color='#e96900'>message</font></code>, string, 警告框内显示的文字信息
    + <code><font color='#e96900'>okTitle</font></code>, string, 确认按钮上显示的文字信息
    + <code><font color='#e96900'>cancelTitle</font></code>, string, 确认按钮上显示的文字信息
- @callback, function，用户操作完成后的回调，参数是按下按钮上的文字信息
    + <code><font color='#e96900'>result</font></code>, string, 用户按下的按钮文字信息

```javascript
    syber.modal.confirm({
        message: 'Do you confirm ?',
        okTitle: 'ok',
        cancelTitle: 'cancel',
    }, function (data) {
        console.log(data.result)
    })
```