---
title: gtoast
---

提示框：提示用户某个操作的简单反馈。

可以设置提示框的内容，2.5秒后提示框自动消失。

支持`Promise` 使用。

> gtoast 为syberos中自带的toast

## syber.modal.gtoast(Object object)
### 参数
#### Object object
| 属性     | 类型  | 默认值 | 必填 | 描述                         |
| ---------- | ------- | -------- | -------- | -------------------------- |
| title | string | | 是 | 内容 |
| success | function |  |  否     | 回调成功      |
| fail   | function |  |  否     | 回调失败      |


#### object.fail回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
```javascript
syber.modal.gtoast({
    title: 'This is gtoast',
    success: function () {
        console.log('success');
    },
    fail: function (error) {
	    console.log('fail: ', error.code, error.msg);
    }
});
```

#### Promise
```javascript
syber.modal.gtoast({
    title: 'This is gtoast'
}).catch(function(error) {
	console.log('fail: ', error.code, error.msg);
});
```