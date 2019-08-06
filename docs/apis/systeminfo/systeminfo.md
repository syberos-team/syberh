---
title: 系统信息
---

# systeminfo

用于手机信息、手机型号、分辨率、内核版本、系统版本

## aboutPhone(modem, callback)

获取手机信息

### 参数

| 参数名   | 类型     | 是否必填 | 描述                                                         |
| -------- | -------- | -------- | ------------------------------------------------------------ |
| modem    | int      | 否       | 在双卡平台可用，默认为0，<br />0：取第一个modem的imei<br />1：取第二个modem的imei |
| callback | function | 否       | 回调函数                                                     |

**回调函数参数**

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



### 示例
```js
syber.systeminfo.aboutPhone(function(data){
	console.log('data: ', data);
});
```


## getModel(callback)

获取手机型号

### 参数

| 参数名   | 类型     | 是否必填 | 描述     |
| -------- | -------- | -------- | -------- |
| callback | function | 否       | 回调函数 |

**回调函数参数**

| 类型   | 是否必填 | 描述     |
| ------ | -------- | -------- |
| String | 否       | 手机型号 |

### 示例

```js
syber.systeminfo.getModel( function(data){
		console.log('data: ', data);
});
```

## getResolution(callback)

获取手机分辨率

### 参数

| 参数名   | 类型     | 是否必填 | 描述     |
| -------- | -------- | -------- | -------- |
| callback | function | 否       | 回调函数 |

**回调函数参数**

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

### 示例

```
syber.systeminfo.getResolution(function(data){
    console.log('screen: ', data);
});
```

## getCoreVersion(callback)

获取内核版本

### 参数

| 参数名   | 类型     | 是否必填 | 描述     |
| -------- | -------- | -------- | -------- |
| callback | function | 否       | 回调函数 |

**回调函数参数**

| 类型   | 是否必填 | 描述       |
| ------ | -------- | ---------- |
| String | 否       | 内核版本号 |

### 示例

```
syber.systeminfo.getCoreVersion(function(data){
    console.log('version: ', data);
});
```

## getSysVersionID(callback)

获取系统版本号

### 参数

| 参数名   | 类型     | 是否必填 | 描述     |
| -------- | -------- | -------- | -------- |
| callback | function | 否       | 回调函数 |

**回调函数参数**

| 类型   | 是否必填 | 描述       |
| ------ | -------- | ---------- |
| String | 否       | 系统版本号 |

### 示例

```
syber.systeminfo.getSysVersionID(function(data){
    console.log('version: ', data);
});
```

