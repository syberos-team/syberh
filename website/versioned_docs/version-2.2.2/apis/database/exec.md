---
title: exec
id: version-2.2.2-exec
original_id: exec
---


操作数据：执行sql语句，不支持查询语句。例如create、drop、insert、delete、update操作。


## syberh.database.exec(Object object)
### **参数**
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| database | string |        | 是       | 数据库名                           |
| sql | string |        | 是       | sql语句，支持绑定参数。例如：insert into test_tbl(id,name) values(?,?)  |
| params | array |        | 否       | sql语句中的绑定参数               |
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
// 无参sql
syberh.database.exec({
  database: "test_db",
  sql: "create table test_tbl(id int, name varchar(20))",
  success: function(result){
    console.log('success', result);
  },
  fail: function(error){
    console.log('fail: ', error.code, error.msg);
  }
});
// 绑定参数
syberh.database.exec({
  database: "test_db",
  sql: "insert into test_tbl(id,name) values(?,?)",
  params: [1, 'jack'],
  success: function(result){
    console.log('success', result);
  },
  fail: function(error){
    console.log('fail: ', error.code, error.msg);
  }
});
```
