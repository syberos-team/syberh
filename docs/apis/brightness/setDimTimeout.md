---
title: setDimTimeout
---

## syberh.brightness.setDimTimeout(Object object)

设置无操作时屏幕进入暗屏状态的时长。

### 权限


### 参数

#### Object object

| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| timeout | string   | 是       | 设置要暗屏时长，单位秒。                                    |
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
    timeout="100",
	success:function(result){
        console.log('result: ', result.result);
    },
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```