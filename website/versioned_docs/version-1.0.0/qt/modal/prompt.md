---
title: promot
id: version-1.0.0-prompt
original_id: prompt
---


### void promot(QString callbackId, QVariant options)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId   | QString | 是       | 回调ID，用于标识每一次的调用 |
| title        | QString | 否       | 标题                     |
| message      | QString | 是       | 内容                     |
| okTitle      | QString | 否       | 确认按钮上显示的文字信息     |
| cancelTitle  | QString | 否       | 取消按钮上显示的文字信息     |

### 信号
### void success(long responseID, QVariant result)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID   | QString | 是       | 回调ID，用于标识每一次的调用 |
| result       | QVariant | 是   | result:  QString 用户按下的按钮上的文字信息<br/> data:  QString 用户输入的文字信息 |