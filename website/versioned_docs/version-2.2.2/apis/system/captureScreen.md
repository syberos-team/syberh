---
title: captureScreen
id: version-2.2.2-captureScreen
original_id: captureScreen
---

## syberh.system.captureScreen(Object object)

截屏

<!-- 支持`Promise` 使用。 -->

### 参数



#### Object object

| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |

#### object.success 回调函数参数
#### 参数
| 属性           | 类型    | 描述                                 |
| -------------- | ------  | ------------------------------------ |
| success       | boolean  | 截屏成功      |

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.system.captureScreen({
	success:function(result){
        console.log('success: ', result.success);
    },
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```
