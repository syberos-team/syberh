---
title: 系统信息
---

# class SystemInfo

用于手机信息、手机型号、分辨率、内核版本、系统版本

## 方法

### void aboutPhone(QString callbackId, int modem)

获取手机信息

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                                                         |
| ---------- | ------- | -------- | ------------------------------------------------------------ |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用                                 |
| modem      | int     | 否       | 在双卡平台可用，默认为0，<br />0：取第一个modem的imei<br />1：取第二个modem的imei |

#### 成功信号

**emit success(long responseID, QVariant result);**

| 参数名     | 类型        | 是否必填 | 描述                         |
| ---------- | ----------- | -------- | ---------------------------- |
| responseID | long        | 是       | 回调ID，用于标识每一次的调用 |
| result     | QJSONObject | 是       | 手机信息                     |

**result**

| 参数名         | 类型   | 是否必填 | 描述                                 |
| -------------- | ------ | -------- | ------------------------------------ |
| id             | String | 是       | 编号                                 |
| name           | String | 是       | 手机名字                             |
| imei           | String | 是       | 移动设备国际识别码                   |
| simCardNumbers | Array  | 是       | 如果是双卡，有多个手机号             |
| imsis          | Array  | 是       | 如果是双卡，有多个国际移动用户识别码 |

```
{
	id:"123",
	name:"红米",
	imei:"45454545"
	simCardNumbers:[
		"15140265546",
		"15140265547"
	],
	imsis:[
		"445545",
		"454545"
	]
}
```



### void getModel(QString callbackId)

获取手机型号

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |

#### 成功信号

**emit success(long responseID, QVariant result);**

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | long    | 是       | 回调ID，用于标识每一次的调用 |
| result     | QString | 是       | 手机型号                     |

### void getResolution(QString callbackId)

获取手机分辨率

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |

#### 成功信号

**emit success(long responseID, QVariant result);**

| 参数名     | 类型        | 是否必填 | 描述                         |
| ---------- | ----------- | -------- | ---------------------------- |
| responseID | long        | 是       | 回调ID，用于标识每一次的调用 |
| result     | QJSONObject | 是       | 分辨率                       |

**result**

| 参数名                 | 类型   | 是否必填 | 描述         |
| ---------------------- | ------ | -------- | ------------ |
| desktopAvallableHeight | int    | 是       | 桌面可用高度 |
| desktopAvallableWidth  | int    | 是       | 桌面可用宽度 |
| devicePlxelRatio       | double | 是       | 分辨比       |
| height                 | int    | 是       | 高度         |
| width                  | int    | 是       | 宽度         |

```
{
	desktopAvallableHeight:1600,
	desktopAvallableWidth:800,
	devicePlxelRatio:2,
	height:1600,
	width:800,
}
```

### void getCoreVersion(QString callbackId)

获取内核版本

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |

#### 成功信号

**emit success(long responseID, QVariant result);**

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | long    | 是       | 回调ID，用于标识每一次的调用 |
| result     | QString | 是       | 版本号                       |

### void getSysVersionID(QString callbackId)

获取系统版本

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用 |

#### 成功信号

**emit success(long responseID, QVariant result);**

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | long    | 是       | 回调ID，用于标识每一次的调用 |
| result     | QString | 是       | 版本号                       |

## 失败信号

### emit failed(long responseID, QVariant errorCode, QString errorMsg);

#### 参数

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | long    | 是       | 回调ID，用于标识每一次的调用 |
| errorCode  | long    | 是       | 错误码                       |
| errorMsg   | QString | 是       | 错误信息                     |