---
title: network-subscribe
---

## syber.system.network-subscribe(Object object)

监听网络连接状态。如果多次调用，仅最后一次调用生效。

<!-- 支持`Promise` 使用。 -->

### 参数

#### Object object


| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |


| 属性    | 类型     | 必填 | 描述                                                         |
| -------       | -------- | -------- | ------------------------------------------------------------   |
| callback      | function | 否       | 每次网络发生变化，都会被回调                                                     |
| fail          | function | 否       | 失败回调                                                         |
| reserved      | Boolean  | 否       | 是否持久化订阅，默认为false。机制：设置为true，页面跳转，不会自动取消订阅，需手动取消订阅 |

#### object.callback 回调函数参数
#### 参数
| 属性            | 类型      | 描述                                 |
| -------------- | ------   | ------------------------------------ |
| metered        | Boolean  | 是否按照流量计费                               |
| type           | String   | 网络类型，可能的值为 2g，3g，4g，wifi，none      |


#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syber.system.aboutPhone({
	success:function(result){
        console.log('handling callback')
    }
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});

```