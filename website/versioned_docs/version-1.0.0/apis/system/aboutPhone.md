---
title: aboutPhone
id: version-1.0.0-aboutPhone
original_id: aboutPhone
---

## syberh.system.aboutPhone(Object object)

获取手机信息。

<!-- 支持`Promise` 使用。 -->

### 参数

#### Object object

| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |

#### object.success 回调函数参数
#### 参数
| 属性           | 类型    | 描述                                 |
| -------------- | ------  | ------------------------------------ |
| deviceId       | String  | 设备ID                               |
| brand          | String  | 设备品牌（下个版本开发）      |
| manufacturer   | String  | 设备生产商（下个版本开发）    |
| model  	     | String  | 设备型号（下个版本开发）  	 |
| name           | String  | 手机名称                             |
| imei           | String  | 移动设备国际识别码                    |
| simCardNumbers | Array   | 双卡有多个手机号              |
| imsis          | Array   | 双卡有多个国际移动用户识别码  |
| kernelVersion  | String  | 内核版本 |
| osType	     | String  | 操作系统名称 |
| osVersionName	 | String  | 操作系统版本名称|
| osVersion	 | Integer | 操作系统版本号|
| osVersionCode	 | Integer | 操作系统小版本号|
| platformVersionCode	| Integer | 运行平台版本号（下个版本开发)|
| screenWidth    | number  | 屏幕宽 |
| screenHeight   | number  | 屏幕高 |
| windowWidth    | number  | 可使用窗口宽度 |
| windowHeight   | number  | 可使用窗口高度 |
| statusBarHeight| String  | 状态栏的高度 |
| pixelRatio     | number  | 设备像素比|
| language       | String  | 系统语言|
| region     	 | String  | 系统地区|

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.system.aboutPhone({
	success:function(result){
        console.log('deviceId: ', result.deviceId);
        console.log('brand: ', result.brand);
        console.log('manufacturer: ', result.manufacturer);
        console.log('model: ', result.model);
        console.log('name: ', result.name);
        console.log('imei: ', result.imei);
        console.log('simCardNumbers: ', result.simCardNumbers);
        console.log('imsis: ', result.imsis);
        console.log('hardware: ', result.hardware);
        console.log('KernelVersion: ', result.KernelVersion);
        console.log('osVersion: ', result.osVersion);
        console.log('osVersionCode: ', result.osVersionCode);
        console.log('softwareVersion: ', result.softwareVersion);
        console.log('screenWidth: ', result.screenWidth);
        console.log('screenHeight: ', result.screenHeight);
        console.log('windowWidth: ', result.windowWidth);
        console.log('windowHeight: ', result.windowHeight);
        console.log('statusBarHeight: ', result.statusBarHeight);
        console.log('pixelRatio: ', result.pixelRatio);
        console.log('language: ', result.language);
        console.log('region: ', result.region);
    }
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```

<!-- #### Promise
```javascript
syberh.system.aboutPhone()
    .then(function(result) {
        console.log('deviceId: ', result.deviceId);
        console.log('brand: ', result.brand);
        console.log('manufacturer: ', result.manufacturer);
        console.log('model: ', result.model);
        console.log('name: ', result.name);
        console.log('imei: ', result.imei);
        console.log('simCardNumbers: ', result.simCardNumbers);
        console.log('imsis: ', result.imsis);
        console.log('hardware: ', result.hardware);
        console.log('KernelVersion: ', result.KernelVersion);
        console.log('osVersion: ', result.osVersion);
        console.log('osVersionCode: ', result.osVersionCode);
        console.log('softwareVersion: ', result.softwareVersion);
        console.log('screenWidth: ', result.screenWidth);
        console.log('screenHeight: ', result.screenHeight);
        console.log('windowWidth: ', result.windowWidth);
        console.log('windowHeight: ', result.windowHeight);
        console.log('statusBarHeight: ', result.statusBarHeight);
        console.log('pixelRatio: ', result.pixelRatio);
        console.log('language: ', result.language);
        console.log('region: ', result.region);
    }).catch(function(error) {
        console.log('fail: ', error.code, error.msg);
    });
``` -->
