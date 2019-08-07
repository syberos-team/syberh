---
title: toast
---

toast()会在一个小浮层里展示关于某个操作的简单反馈。例如，在邮件发送前离开邮件编辑界面，可以触发一个“草稿已保存”的 toast，告知用户以后可以继续编辑。toast 会在显示一段时间之后自动消失


## syber.modal.toast(Object object)
### 参数
#### Object object
| 属性     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| title | string | 是 | 提示的内容 |
| icon | string | 是 | 图标 |
| image | string | 否 | 自定义图标的本地路径，image 的优先级高于 icon |


#### object.icon 的合法值
| 值     | 说明    |       
| ---------- | ------- | 
| success | 显示成功图标，此时 title 文本最多显示 7 个汉字长度 |
| loading | 显示加载图标，此时 title 文本最多显示 7 个汉字长度 |
| none | 不显示图标，此时 title 文本最多可显示两行 |


### 代码示例
```javascript
    syber.modal.toast({
        title: 'This is a toast',
        icon: 'success'
    })
```