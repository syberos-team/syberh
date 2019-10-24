---
title: sendNotification
---


发送通知消息：向状态栏发送消息，发送成功则返回true。消息将显示在状态栏中，点击消息将进入应用。


> 发送通知消息属于敏感权限,必须获取通知权限,在sopconfig.xml文件中添加如下字段:

``` javascript
<uses-permission syberos:name="syberos.permission.ACCESS_NOTIFICATION"/>
```

## syberh.notification.sendNotification(Object object)
### **参数**
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| type | int | 3       | 是       | 通知类型                           |
| title | String |        | 否       | 标题                           |
| subtitle | String |        | 否       | 子标题                           |
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

#### object.type 的合法值
| 值     | 说明    |
| ---------- | ------- |
| 1 | 通知在状态栏显示完成后， 自动删除 |
| 2 | 通知发送时间不显示在下拉列表上 |
| 3 | 通知在手机重启后， 自动删除 |

**object.success回调函数**
#### 参数
| 属性 | 类型   | 描述         |
| ---- | ------ | ------------ |
| result | boolean  | 是     | 返回true, 表示执行成功  |

**object.fail回调函数**
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **代码示例**
``` javascript
syberh.notification.sendNotification({
	success: function(result){
    type: 3,
    title: "消息标题“,
    subtitle: ”消息子标题“,
		console.log('success: ', result);
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```