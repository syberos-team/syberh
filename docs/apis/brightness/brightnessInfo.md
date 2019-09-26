---
title: brightnessInfo
---

## syberh.brightness.brightnessInfo(Object object)

获取系统亮度信息。

### 权限


### 参数

#### Object object

| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |


#### object.success 回调函数参数
#### 参数
| 属性            | 类型      | 描述                                 |
| -------------- | ------   | ------------------------------------ |
| maximumBrightness      | int  | 系统最大亮度值 。|
| brightness     | int      |当前屏幕亮度值                           |
| blankTime      | int      |当前的息屏时长，单位秒。                   |
| dimTimeout      | int      |获取当前的进入暗屏状态的时长。，单位秒。                   |
| ambientLightSensorEnabled      | int      |获取环境光感器开关状态（自动调节亮度）,true 使能态，false 关闭态                 |
| adaptiveDimmingEnabled         | int      |获取自适应调光开关状态,true 使能；false 关闭                    |

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.brightness.brightnessInfo({
	success:function(result){
        console.log('maximumBrightness: ', result.maximumBrightness);
        console.log('brightness: ', result.brightness);
        console.log('blankTime: ', result.blankTime);
        console.log('dimTimeout: ', result.dimTimeout);
        console.log('ambientLightSensorEnabled: ', result.ambientLightSensorEnabled);
        console.log('adaptiveDimmingEnabled: ', result.adaptiveDimmingEnabled);

    },
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```