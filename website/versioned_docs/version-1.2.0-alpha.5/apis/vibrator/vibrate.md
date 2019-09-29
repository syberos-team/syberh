---
title: vibrate
id: version-1.2.0-alpha.5-vibrate
original_id: vibrate
---

## syberh.vibrator.vibrate(Object object)

触发震动

### 权限


### 参数

#### Object object

| 属性    | 类型     | 必填 | 描述                |
| ------- | -------- | -------- | ------------|
| mode    | String   | 否       | 振动模式，"long"表示长振动，"short"表示短振动。默认为 long     |
| success | function | 否       | 成功回调      |
| fail    | function | 否       | 失败回调      |


#### object.success 回调函数参数
#### 参数


#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.vibrator.vibrate({
    mode:“long”,
	success:function(result){
        console.log('maximumBrightness: ', result.maximumBrightness);

    },
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```