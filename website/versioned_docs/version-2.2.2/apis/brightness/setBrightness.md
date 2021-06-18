---
title: setBrightness
id: version-2.2.2-setBrightness
original_id: setBrightness
---

## syberh.brightness.setBrightness(Object object)

设置屏幕亮度。

### 权限


### 参数

#### Object object

| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| brightness | number   | 是       | 设置屏幕亮度，范围0-100。                                    |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |


#### object.success 回调函数参数
#### 参数
| 属性   | 类型    | 必填 | 描述                    |
| ------ | ------- | ---- | ----------------------- |
| result | boolean | 是   | 返回 true, 表示执行成功 |

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.brightness.setDimTimeout({
    brightness: 100,
	success:function(result){
        console.log('result: ', result.result);
    },
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```