---
title: 检查更新
id: version-1.6.0-check
original_id: check
---

## syberh.update.check()

> 前提：在企业商店上架，并且修改[storeBaseUrl](/docs/app-config.html)
 
检查服务器上是否有新版本


#### object.success 回调函数参数
#### 参数
| 属性           | 类型    | 描述                                 |
| -------------- | ------  | ------------------------------------ |
| oldCode        | String  | 当前版本号                             |
| vercode        | String  | 服务器上的版本号                |
| isNeedUpdate   | String  | 是否需要更新                |

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
  syberh.update.check({
    success: function(res) {
      console.log('检测更新返回版本～', JSON.stringify(res))
    },
    fail: function(error) {
      console.log('error: ', error.code, error.msg)
    }
  })
```
