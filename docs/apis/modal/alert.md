---
title: alert
---

弹出框：提示或警告用户。

可以设置弹出框的标题、标题图标、内容、按钮文字、按钮文字颜色，仅支持成功、警告图标，用户点击关闭。

<!-- 支持`Promise` 使用。 -->



## syber.modal.alert(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| title | string |  | 否 | 标题，最多7个汉字 |
| titleIcon | string |       | 否 | 标题图标 |
| content | string |  | 是 | 显示内容 |
| confirmText | string | 确定 | 否 | 按钮文字，最多4个汉字 |
| confirmColor | string| #007aff  | 否 | 按钮文字颜色 |
| success | function |  |  否     | 回调成功      |
| fail   | function |  |  否     | 回调失败      |


#### object.titleIcon 的合法值
| 值     | 说明    |       
| ---------- | ------- | 
| success | 成功图标 |
| warning | 警告图标 |


#### object.fail回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
```javascript
syber.modal.alert({
    content: 'This is a alert',
    success: function() {
        console.log('success');            
    },
    fail: function(error) {
        console.log('fail: ', error.code, error.msg);
    }
})
```

<!-- #### Promise
```javascript
syber.modal.alert({
    content: 'This is a alert',
}).then(function() {
    console.log('success');
}).catch(function(error) {
    console.log('fail: ', error.code, error.msg);
})
``` -->

#### 原生alert调用
```javascript
alert('This is a alert')
```
