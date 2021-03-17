---
title: databaseExists
---


判断指定数据库文件是否存在。


## syberh.database.databaseExists(Object object)
### **参数**
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| database | string |        | 是       | 数据库名                           |
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
| code | string | 错误码   |
| msg  | string | 错误消息 |



### **代码示例**
``` javascript
syberh.database.databaseExists({
  database: "test_db",
  success: function(result){
    console.log('success', result);
  },
  fail: function(error){
    console.log('fail: ', error.code, error.msg);
  }
});
```
