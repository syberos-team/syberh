---
title: networkEnabled
---

## syberh.cellular.networkEnabled(Object object)

设置数据网络状态为启用。

### 权限
需要申请 `syberos.permission.ADMIN_DATA_NETWORK` 敏感权限才可以调用

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
| isEnabled      | boolean  | 设置数据网络状态为启用， 设置成功返回 true ，失败返回 false 。|


#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.cellular.networkEnabled({
    flag:true,
	success:function(result){
        console.log('isEnabled: ', result.isEnabled);

    },
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```