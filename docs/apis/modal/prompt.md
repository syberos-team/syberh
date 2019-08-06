---
title: prompt
---

提示框经常用于提示用户在进入页面前输入某个值。当提示框出现后，用户需要输入某个值，然后点击确认或取消按钮才能继续操作。


### prompt(options, callback)

- @options
    + <code><font color='#e96900'>message</font></code>, string, 警告框内显示的文字信息
    + <code><font color='#e96900'>okTitle</font></code>, string, 确认按钮上显示的文字信息
    + <code><font color='#e96900'>cancelTitle</font></code>, string，取消按钮上显示的文字信息
- @callback, function，用户操作完成后的回调
    + <code><font color='#e96900'>res.result</font></code>：用户按下的按钮上的文字信息
    + <code><font color='#e96900'>res.data</font></code>：用户输入的文字信息

```javascript
    syber.modal.prompt({
        message: 'This is a prompt',
        duration: 0.3
    }, function (value) {
        console.log('prompt callback', value)
    })
```