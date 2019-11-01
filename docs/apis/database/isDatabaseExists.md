---
title: isDatabaseExists
---


判断指定数据库文件是否存在。


## syberh.database.isDatabaseExists(Object object)
### **参数**
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| databaseName | string |        | 是       | 数据库名                           |
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

#### object.success回调函数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | 返回true, 表示存在  |

#### object.fail回调函数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **代码示例**
``` javascript
syberh.database.isDatabaseExists({
  databaseName: "",
	success: function(result){
    console.log('success', result);  
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
