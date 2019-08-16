---
title: 拨号
---

# class Telephony

电话拨打接听等控制与状态监控

## 方法

### void dial(QString callbackId, QString phoneNumber)

拨号

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                                                         |
| ---------- | ------- | -------- | ------------------------------------------------------------ |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用                                 |
| phoneNumber| QString | 是       | 对方号码 |

## 成功信号

### emit success(long responseID, QVariantMap result)

| 参数名     | 类型        | 是否必填 | 描述                         |
| ---------- | ----------- | -------- | ---------------------------- |
| responseID | long        | 是       | 回调ID，用于标识每一次的调用 |

## 失败信号

### emit failed(long responseID, QVariant errorCode, QString errorMsg)

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | long    | 是       | 回调ID，用于标识每一次的调用 |
| errorCode  | long    | 是       | 错误码                       |
| errorMsg   | QString | 是       | 错误信息                     |