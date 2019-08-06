---
title: alert
---

警告框经常用于确保用户可以得到某些信息。当警告框出现后，用户需要点击确定按钮才能继续进行操作。


### alert(options, callback)

- @options
    + <code><font color='#e96900'>message</font></code>, string, 警告框内显示的文字信息
    + <code><font color='#e96900'>okTitle</font></code>, string, 确认按钮上显示的文字信息
- @callback, function，用户操作完成后的回调

```javascript
    syber.modal.alert({
        message: 'This is a alert',
        okTitle: '确认'
    }, function () {
        console.log('alert callback')
    })
```
