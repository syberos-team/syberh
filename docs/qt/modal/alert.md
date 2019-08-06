---
title: alert
---

### void alert(QString callbackId, QVariant options)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |
| title      | QString | 否       | 标题                     |
| message    | QString | 是       | 内容                     |

### 信号
### void success(long responseID, bool result)
| 参数名     | 类型    | 是否必填 | 描述                            |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | QString | 是       | 回调ID，用于标识每一次的调用      |
| result     | bool    | 是       |  告诉页面调用成功               |
