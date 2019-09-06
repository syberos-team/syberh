---
title: network-unsubscribe
---

## syber.system.network-unsubscribe(Object object)

取消监听网络连接状态。

<!-- 支持`Promise` 使用。 -->

### 参数

#### Object object


| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |

### 代码示例
```js
()
syber.system.network-unsubscribe();

```