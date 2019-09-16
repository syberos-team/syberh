---
title: 剪贴板
id: version-1.1.0-clipboard
original_id: clipboard
---

用于获取、设置剪切板内容，目前只支持字符串类型

# class Clipboard
操作剪贴板相关功能，都有该类提供


## 方法

### void setString(QString callbackId, QString content)

向系统剪贴板设置内容

#### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |
| content    | QString | 是       | 设置在剪贴板中的内容         |

#### 成功信号

**emit success(long responseID, QVariant result);**

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | long    | 是       | 回调ID，用于标识每一次的调用 |
| result     | QString | 是       | success                      |


### QString getString(QString callbackId)

从系统剪贴板获取内容

#### 参数
| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |

#### 成功信号

**emit success(long responseID, QVariant result);**

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | long    | 是       | 回调ID，用于标识每一次的调用 |
| result     | QString | 是       | 获取到剪贴板中的内容         |

## 失败信号

### emit failed(long responseID, QVariant long errorCode, QString errorMsg);

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | long    | 是       | 回调ID，用于标识每一次的调用 |
| errorCode  | long    | 是       | 错误码                       |
| errorMsg   | QString | 是       | 错误信息                     |




