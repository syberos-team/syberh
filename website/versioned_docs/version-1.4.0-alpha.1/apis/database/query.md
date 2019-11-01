---
title: query
id: version-1.4.0-alpha.1-query
original_id: query
---


查询数据：根据sql语句查询表中数据，查询成功则返回查询结果。例如查询所有、条件查询操作。



## syberh.database.query(Object object)
### **参数**
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| databaseName | string |        | 是       | 数据库名                           |
| sql | string |        | 是       | sql语句                           |
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

#### object.success回调函数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | array  | 是     | 返回查询结果  |

#### object.fail回调函数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **代码示例**
``` javascript
syberh.database.query({
  databaseName: "",
  sql: "xxxx",
	success: function(result){
    console.log('success', result);  
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
