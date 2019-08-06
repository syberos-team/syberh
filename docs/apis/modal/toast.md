---
title: toast
---

toast() 会在一个小浮层里展示关于某个操作的简单反馈。例如，在邮件发送前离开邮件编辑界面，可以触发一个“草稿已保存”的 toast，告知用户以后可以继续编辑。toast 会在显示一段时间之后自动消失。


### toast(options)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| message | string | 是 | 展示的内容 |

### 代码示例
```javascript
    syber.modal.toast({
        message: 'This is a toast'
    })
```