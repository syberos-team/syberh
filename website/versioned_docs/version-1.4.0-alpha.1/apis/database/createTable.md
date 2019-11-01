---
title: createTable
id: version-1.4.0-alpha.1-createTable
original_id: createTable
---


创建表：将在应用程序或者服务的私有数据目录下新增数据库，数据库创建成功后，将根据表sql、索引sql继续创建表、索引。全部创建成功则返回true。


## syberh.database.createTable(Object object)
### **参数**
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| databaseName | string |        | 是       | 数据库名                           |
| sql | string |        | 是       | 表sql                           |
| sqlindex | string |        | 否       | 索引sql                           |
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

#### object.success回调函数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | 返回true, 表示执行成功  |

#### object.fail回调函数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **代码示例**
``` javascript
syberh.database.createTable({
  databaseName: "",
  sql: "xxxx",
  sqlindex: "xxxx",
	success: function(result){
    console.log('success', result);  
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
