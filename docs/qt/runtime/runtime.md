---
title: runtime
---

# class Runtime

`runtime` 模块管理运行环境，可用于获取当前运行环境信息、与其它程序进行通讯等。

## 方法

### void launchApp(QString callbackId, QString url)

一个应用希望启动另一个应用时调用

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |
| url        | QString | 是       | app地址                      |

#### 成功信号

**void success(long responseID, QVariant result);**

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | long    | 是       | 回调ID，用于标识每一次的调用 |
| result     | QString | 是       | success                      |

### void launchApp(QString callbackId, QString appid, QStringList params)

当一个应用希望启动本包中的另一个应用时

#### 参数

| 参数名     | 类型        | 是否必填 | 描述                         |
| ---------- | ----------- | -------- | ---------------------------- |
| callbackId | QString     | 是       | 回调ID，用于标识每一次的调用 |
| appid      | QString     | 是       | app地址                      |
| params     | QStringList | 否       | 参数列表                     |

#### 成功信号

**void success(long responseID, QVariant result);**

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | long    | 是       | 回调ID，用于标识每一次的调用 |
| result     | QString | 是       | success                      |

## 失败信号

### void failed(long responseID, QVariant errorCode, QString errorMsg);

#### 参数

- callbackId:	回调ID，用于标识每一次的调用
- errorCode:	错误码
- result:	错误信息

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | long    | 是       | 回调ID，用于标识每一次的调用 |
| errorCode  | long    | 是       | 错误码                       |
| errorMsg   | QString | 是       | 错误信息                     |

