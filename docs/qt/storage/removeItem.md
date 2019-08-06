---
title: removeItem
---

传入一个键名将会删除本地存储中对应的键值

### void removeItem(QString callbackId, QString key)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |
| key        | QString | 是       | 键名 |

### 信号
### void success(long responseID, bool result)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ----------------------------  |
| responseID   | QString     | 是       | 回调ID，用于标识每一次的调用       |
| result       | bool    | 是       | 告诉页面执行成功  |