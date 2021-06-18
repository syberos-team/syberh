---
title: query
id: version-2.2.2-query
original_id: query
---


查询数据：执行查询sql，返回查询数据。



## syberh.database.query(Object object)
### **参数**
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| database | string |        | 是       | 数据库名                           |
| sql | string |        | 是       | sql语句，支持绑定参数。例如： select * from test_tbl where id = ? |
| params | array |        | 否       | sql语句中的绑定参数               |
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
// 无参数sql
syberh.database.query({
  database: "test_db",
  sql: "select * from test_tbl",
  success: function(result){
    console.log('success', result);
  },
  fail: function(error){
    console.log('fail: ', error.code, error.msg);
  }
});
// 绑定参数
syberh.database.query({
  database: "test_db",
  sql: "select * from test_tbl where id=? and name=?",
  params: [1, 'jack'],
  success: function(result){
    console.log('success', result);
  },
  fail: function(error){
    console.log('fail: ', error.code, error.msg);
  }
});
```
