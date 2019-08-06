---
title: getItem
---

传入键名返回对应的键值。

### getItem(QString callbackId, QString key)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |
| key        | QString | 是       | 键名 |

### 信号
### void success(long responseID, QVariant result)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ----------------------------  |
| responseID   | QString     | 是       | 回调ID，用于标识每一次的调用       |
| result       | QVariant    | 是       | result: QVariant 返回对应的键值  |