---
title: battery
id: version-1.0.0-battery
original_id: battery
---

## syberh.system.battery(Object object)

获取当前设备的电量信息。

### 参数

#### Object object

| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |


#### object.success 回调函数参数
#### 参数
| 属性           | 类型      | 描述                                 |
| -------------- | ------   | ------------------------------------|
| isCharging     | boolean  | 是否正在充电                          |
| level          | Number   | 当前电量，0 - 100 之间                 |
| capacity       | Number   | 电池容量，0 - 100 之间                 |
| isValid        | boolean  | 电池是否有效                          |

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.battery.getStatus({
	success:function(result){
        console.log('isCharging: ', result.isCharging);
        console.log('level: ', result.level);
        console.log('capacity: ', result.capacity);
        console.log('isValid: ', result.isValid);
    },
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```

