---
title: Date
---

## syberh.system.setDate(Object object)

设置系统时间

<!-- 支持`Promise` 使用。 -->

### 参数



#### Object object

| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| date | String  | 是      | 设置的时间,格式(yyyy-MM-dd hh:mm:ss)      |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |

#### object.success 回调函数参数
#### 参数
| 属性           | 类型    | 描述                                 |
| -------------- | ------  | ------------------------------------ |
| date       | String  | 当前系统时间,格式(yyyy-MM-dd hh:mm:ss)      |

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.system.setDate({
	success:function(result){
        console.log('date: ', result.date);
    },
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```
