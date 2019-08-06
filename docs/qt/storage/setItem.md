---
title: setItem
---

该方法可以通过键值对的形式将数据存储到本地。同时可以通过该方法，更新已有的数据。

### void setItem(QString callbackId, QString key, QVariant value)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |
| key        | QString | 是       | 键名 |
| value      | QString | 是       | 键值 |

### 信号
### void success(long responseID, bool result)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ----------------------------  |
| responseID   | QString     | 是       | 回调ID，用于标识每一次的调用       |
| result       | bool    | 是       | 告诉页面执行成功  |