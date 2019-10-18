---
title: setDimTimeout
id: version-1.3.0-alpha.1-setDimTimeout
original_id: setDimTimeout
---

## syberh.brightness.setDimTimeout(Object object)

设置无操作时屏幕进入暗屏状态的时长。

### 如何生效(两个条件都满足才会生效)
- 条件一： 需要比系统设置，休眠时间长
- 条件二： 需要比自定义的时间大（每次把最大值写入配置文件，且不会删除）

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