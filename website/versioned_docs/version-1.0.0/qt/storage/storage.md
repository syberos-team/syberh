---
title: 本地存储
id: version-1.0.0-storage
original_id: storage
---

# class Storage

对本地数据进行存储、修改、删除，并且该数据是永久保存的，除非手动清除或者代码清除

## 方法

### void setItem(QString callbackId, QString key, QVariant value)

该方法可以通过键值对的形式将数据存储到本地。同时可以通过该方法，更新已有的数据。

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |
| key        | QString | 是       | 键名 |
| value      | QString | 是       | 键值 |

## 成功信号

### emit success(long responseID, QVariant result)

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ----------------------------  |
| responseID   | QString     | 是       | 回调ID，用于标识每一次的调用       |
| result       | boolean    | 是       | 存储成功返回true |


## 方法

### void getItem(QString callbackId, QString key)

传入键名返回对应的键值。

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |
| key        | QString | 是       | 键名 |

## 成功信号

### emit success(long responseID, QVariant result)

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ----------------------------  |
| responseID   | QString     | 是       | 回调ID，用于标识每一次的调用       |
| result       | QVariant    | 是       | 返回存储的键值  |


## 方法

### void removeItem(QString callbackId, QString key)

传入一个键名将会删除本地存储中对应的键值。

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |
| key        | QString | 是       | 键名 |

## 成功信号

### emit success(long responseID, QVariantMap result)

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ----------------------------  |
| responseID   | QString     | 是       | 回调ID，用于标识每一次的调用       |
| result       | QVariant    | 是       | 删除成功时返回true |


## 方法

### void getAllKeys(QString callbackId)

返回一个包含全部已存储项键名的数组。

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |

## 成功信号

### emit success(long responseID, QVariantMap result)

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ----------------------------  |
| responseID   | QString     | 是       | 回调ID，用于标识每一次的调用       |
| result       | QVariant    | 是       | 返回所有的键名的数组 |


---

## 失败信号

### emit failed(long responseID, QVariant errorCode, QString errorMsg)

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | long    | 是       | 回调ID，用于标识每一次的调用 |
| errorCode  | long    | 是       | 错误码                       |
| errorMsg   | QString | 是       | 错误信息                     |