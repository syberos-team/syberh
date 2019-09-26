---
title: vibrateInfo
---

## syberh.vibrator.vibrateInfo(Object object)

查询震动设置

### 权限


### 参数

#### Object object

| 属性    | 类型     | 必填 | 描述                |
| ------- | -------- | -------- | ------------|
| success | function | 否       | 成功回调      |
| fail    | function | 否       | 失败回调      |


#### object.success 回调函数参数
#### 参数
| 属性            | 类型      | 描述                                 |
| -------------- | ------   | ------------------------------------ |
| touch          | boolean  | 获取物理按键是否震动。物理按键震动开启返回true；否则返回false。                       |
| vibrating      | boolean  | 获取键盘按键震动是否开启。键盘按键震动开启返回true；否则返回false。                         |

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.vibrator.vibrateInfo({
	success:function(result){
        console.log('touch: ', result.touch);
        console.log('vibrating: ', result.vibrating);
    },
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```