---
title: badgeShow
---


角标显示：应用图标右上角显示应用消息条数 。

可以对应用图标右上角消息条数进行设置，设置成功则返回true。

> 角标显示属于敏感权限,必须获取通知权限,在sopconfig.xml文件中添加如下字段:

``` javascript
<uses-permission syberos:name="syberos.permission.ACCESS_NOTIFICATION"/>
```

## syberh.notification.badgeShow(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| appId | String |       | 是       | 应用id                           |
| num | number |  0     | 否       | 消息条数                           |
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

### object.success回调函数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | 返回true, 表示执行成功  |

### object.fail回调函数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |


### 代码示例
``` javascript
syberh.notification.badgeShow({
	success: function(result){
    appId: "app",
    num: 3,
		console.log('success: ', result);
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
