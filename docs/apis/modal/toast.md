---
title: toast
---

toast()会在一个小浮层里展示关于某个操作的简单反馈。例如，在邮件发送前离开邮件编辑界面，可以触发一个“草稿已保存”的 toast，告知用户以后可以继续编辑。toast 会在显示一段时间之后自动消失，支持Promise调用


## syber.modal.toast(Object object)
### 参数
#### Object object
| 属性     | 类型  | 默认值 | 必填 | 描述                         |
| ---------- | ------- | -------- | -------- | -------------------------- |
| title | string | | 是 | 提示的内容 |
| icon | string | 'success' | 是 | 图标 |
| duration | number | 1500 | 否 | 提示的延迟时间 |
| success | function |  |  否     | 接口调用成功的回调函数      |
| fail   | function |  |  否     | 接口调用失败的回调函数      |


#### object.icon 的合法值
| 值     | 说明    |
| ---------- | ------- |
| success | 显示成功图标，此时 title 文本最多显示 7 个汉字长度 |
| error | 显示错误图标，此时 title 文本最多显示 7 个汉字长度 |
| none | 不显示图标，此时 title 文本最多可显示两行（14个汉字长度） |


#### object.fail回调函数
#### Object object
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
```javascript
//success图标
syber.modal.toast({
    title: 'This is a toast',
    icon: 'success',
    success:function(){
        console.log('toast执行成功')
    }
    fail:function(error){
        console.log('code: ', error.code);
        console.log('msg: ', error.msg);
	}
});
```

#### Promise
```javascript
syber.modal.toast({
    title: '我是没有图标的toast，但是我最大只能14个汉字',
    icon: 'none',
}).then(function() {
    console.log('toast执行成功')
}).catch(function(error) {
    console.log('code: ', error.code);
    console.log('msg: ', error.msg);
});
```