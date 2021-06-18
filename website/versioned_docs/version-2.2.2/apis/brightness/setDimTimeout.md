---
title: setDimTimeout
id: version-2.2.2-setDimTimeout
original_id: setDimTimeout
---

## syberh.brightness.setDimTimeout(Object object)

设置息屏时长。


### 权限


### 参数

#### Object object

| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| timeout | number   | 是       | 设置要暗屏时长，单位秒，仅支持 15/30/60/300/600    |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |


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
syberh.brightness.setDimTimeout({
    timeout: 30,
	success:function(result){
        console.log('result: ', result.result);
    },
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```