---
title: gtoast
---

gtoast()会在一个小浮层里展示关于某个操作的简单反馈。例如，在邮件发送前离开邮件编辑界面，可以触发一个“草稿已保存”的 gtoast，告知用户以后可以继续编辑。gtoast会在显示一段时间之后自动消失，支持Promise调用


## syber.modal.gtoast(Object object)
### 参数
#### Object object
| 属性     | 类型  | 默认值 | 必填 | 描述                         |
| ---------- | ------- | -------- | -------- | -------------------------- |
| title | string | | 是 | 提示的内容 |
| success | function |  |  否     | 接口调用成功的回调函数      |
| fail   | function |  |  否     | 接口调用失败的回调函数      |


#### object.fail回调函数
#### 参数
#### Object object
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
```javascript
syber.modal.gtoast('This is gtoast');

syber.modal.gtoast({
    title: 'This is gtoast',
    icon: 'success',
    success:function(result){
        console.log('result: ', result);
    }
    fail:function(error){
        console.log('code: ', error.code);
        console.log('msg: ', error.msg);
	}
});

syber.modal.gtoast({
    title: 'This is gtoast'
}).then(function(result) {
    console.log('result: ', result);
}).catch(function(error) {
    console.log('code: ', error.code);
    console.log('msg: ', error.msg);
});
```