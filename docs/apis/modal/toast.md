---
title: toast
---

toast()会在一个小浮层里展示关于某个操作的简单反馈。例如，在邮件发送前离开邮件编辑界面，可以触发一个“草稿已保存”的 toast，告知用户以后可以继续编辑。toast 会在显示一段时间之后自动消失


## syber.modal.toast(Object object)
### 参数
#### Object object
| 属性     | 类型  | 默认值 | 必填 | 描述                         |
| ---------- | ------- | -------- | -------- | -------------------------- |
| title | string | | 是 | 提示的内容 |
| icon | string | 'success' | 是 | 图标 |
| image | string |  | 否 | 自定义图标的本地路径，image 的优先级高于 icon |
| duration | number | 2000 | 否 | 提示的延迟时间 |
| success | function |  |  否     | 接口调用成功的回调函数      |
| error   | function |  |  否     | 接口调用失败的回调函数      |


#### object.icon 的合法值
| 值     | 说明    |       
| ---------- | ------- | 
| success | 显示成功图标，此时 title 文本最多显示 7 个汉字长度 |
| loading | 显示加载图标，此时 title 文本最多显示 7 个汉字长度 |
| none | 不显示图标，此时 title 文本最多可显示两行 |


#### object.error回调函数
#### 参数
#### Object err
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
```javascript
    syber.modal.toast({
        title: 'This is a toast',
        icon: 'success'
    })
```