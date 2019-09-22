---
title: 路由(router)
---

router 模块提供了一系列的当前窗口操作，例如 reLaunch、navigateTo、redirectTo、goBack、 reload等


## syberh.router.reLaunch(Object object)

关闭所有页面，打开到应用内的某个页面

### 参数
#### Object object
| 属性    | 类型     | 默认值 | 必填 | 描述                   |
| ------- | -------- | ------ | ---- | ---------------------- |
| url     | string   |        | 是   | 需要跳转的应用内页面的路径, 路径后可以带参数。参数与路径之间使用 ? 分隔，参数键与参数值用 = 相连，不同参数用 & 分隔；如 'index.html?key=value&key2=value2'          |
|data|object||否|页面参数,如果有则会拼接到路径后面,如 {key3:value3}转换为'key3=value3'
| success | function |        | 否   | 回调成功 |
| fail    | function |        | 否   | 回调失败 |


#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | 返回true, 表示执行成功  |

#### object.fail 回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
``` javascript
syberh.router.reLaunch({
  url:'index.html',
  data:{key:123}
  success:function(result){
    console.log('success',result); 
  },
  fail:function(error){
    console.log('fail: ', error.code, error.msg);
  }
})
```


## syberh.router.redirectTo(Object object)

跳转到应用内的某个页面,不关闭当前页面，返回键会回到上一个历史页面

### 参数
#### Object object
| 属性    | 类型     | 默认值 | 必填 | 描述                   |
| ------- | -------- | ------ | ---- | ---------------------- |
| url     | string   |        | 是   | 需要跳转的应用内页面的路径, 路径后可以带参数。参数与路径之间使用 ? 分隔，参数键与参数值用 = 相连，不同参数用 & 分隔；如 'index.html?key=value&key2=value2'          |
|data|object||否|页面参数,如果有则会拼接到路径后面,如 {key3:value3}转换为'key3=value3'
| success | function |        | 否   | 回调成功 |
| fail    | function |        | 否   | 回调失败 |


#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | 返回true, 表示执行成功  |

#### object.fail 回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
``` javascript
syberh.router.redirectTo({
  url:'index.html',
  data:{key,123}
  success:function(result){
    console.log('success',result); 
  },
  fail:function(error){
    console.log('fail: ', error.code, error.msg);
  }
})
```

## syberh.router.reload()

重新加载当前页面

### 参数
#### Object object
| 属性    | 类型     | 默认值 | 必填 | 描述                   |
| ------- | -------- | ------ | ---- | ---------------------- |
| success | function |        | 否   | 回调成功 |
| fail    | function |        | 否   | 回调失败 |


#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | 返回true, 表示执行成功  |

#### object.fail 回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
``` javascript
syberh.router.reload({
  success:function(result){
    console.log('success',result); 
  },
  fail:function(error){
    console.log('fail: ', error.code, error.msg);
  }
})
```

## syberh.router.navigateTo(Object object)

保留当前页面，跳转到应用内的某个页面。

### 参数
#### Object object
| 属性    | 类型     | 默认值 | 必填 | 描述                   |
| ------- | -------- | ------ | ---- | ---------------------- |
| url     | string   |        | 是   | 需要跳转的应用内页面的路径, 路径后可以带参数。参数与路径之间使用 ? 分隔，参数键与参数值用 = 相连，不同参数用 & 分隔；如 'index.html?key=value&key2=value2'          |
|data|object||否|页面参数,如果有则会拼接到路径后面,如 {key3:value3}转换为'key3=value3'
| success | function |        | 否   | 回调成功 |
| fail    | function |        | 否   | 回调失败 |


#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | 返回true, 表示执行成功  |

#### object.fail 回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
``` javascript
syberh.router.navigateTo({
  url:'index.html',
  success:function(result){
    console.log('success',result); 
  },
  fail:function(error){
    console.log('fail: ', error.code, error.msg);
  }
})
```


## syberh.router.navigateBack(Object object)

关闭当前页面，返回上一页面(目前不支持多页面返回)

### 参数
#### Object object
| 属性    | 类型     | 默认值 | 必填 | 描述                   |
| ------- | -------- | ------ | ---- | ---------------------- |
<!--| delta     | number   |  1      | 否   | 返回的页面数，如果 delta 大于现有页面数，则返回到首页。          |-->
| success | function |        | 否   | 回调成功 |
| fail    | function |        | 否   | 回调失败 |


#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | 返回true, 表示执行成功  |

#### object.fail 回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
``` javascript
syberh.router.redirectTo({
  url:'https://baidu.com',
  success:function(result){
    console.log('success',result); 
  },
  fail:function(error){
    console.log('fail: ', error.code, error.msg);
  }
})
```

## syberh.router.goBack()

返回

### 参数

#### Object object

| 属性    | 类型     | 默认值 | 必填 | 描述                   |
| ------- | -------- | ------ | ---- | ---------------------- |
| success | function |        | 否   | 回调成功 |
| fail    | function |        | 否   | 回调失败 |


#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | 返回true, 表示执行成功  |

#### object.fail 回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |


### 代码示例
``` javascript
syberh.router.goBack({
  success:function(result){
    console.log('success',result); 
  },
  fail:function(error){
    console.log('fail: ', error.code, error.msg);
  }
})
```

