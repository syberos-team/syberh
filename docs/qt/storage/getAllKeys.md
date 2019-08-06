---
title: getAllKeys
---

返回一个包含全部已存储项键名的数组。

### void getAllKeys(QString callbackId)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |

### 信号
### void success(long responseID, QVariant result)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID   | QString     | 是       | 回调ID，用于标识每一次的调用 |
| result       | QVariant    | 是       | result:QVariant 返回一个包含全部已存储项键名的数组           |