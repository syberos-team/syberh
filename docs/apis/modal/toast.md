---
title: toast
---

提示框：提示用户某个操作的简单反馈。

可以设置提示框的标题、标题图标、内容、提示时长，仅支持成功、错误图标，到时提示框自动消失。

<!-- 支持`Promise` 使用。 -->


## syberh.modal.toast(Object object)
### 参数
#### Object object
| 属性     | 类型  | 默认值 | 必填 | 描述                         |
| ---------- | ------- | -------- | -------- | -------------------------- |
| title | string | | 是 |标题：显示图标时，最多7个汉字；不显示图标时，最多14个汉字 |
| icon | string | success | 是 | 标题图标 |
| duration | number | 1500 | 否 | 提示时长（毫秒） |
| success | function |  |  否     | 回调成功      |
| fail   | function |  |  否     | 回调失败      |


#### object.icon 的合法值
| 值     | 说明    |
| ---------- | ------- |
| success | 成功图标 |
| error | 错误图标 |
| none | 不显示图标 |


#### object.fail回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
```javascript
syberh.modal.toast({
    title: '提示',
    icon: 'success',
    success: function () {
        console.log('success');  
    },
    fail: function (error) {
	    console.log('fail: ', error.code, error.msg);
    }
});
```

<!-- #### Promise
```javascript
syberh.modal.toast({
    title:"我是没有图标的toast，但是我最大只能14个汉字",
    icon:"none"
}).then(function() {
    console.log('success');  
}).catch(function(error) {
    console.log('fail: ', error.code, error.msg);
})
``` -->