---
title: webview
---

> `webview`模块目前只提供对当前页面的操作,不支持多 webview。

webview 模块提供了一系列的当前操作接口，例如 goBack、redirectTo 和 reload。



## syber.webview.reload()

重新加载当前页面

### 参数
#### Object object
| 属性    | 类型     | 默认值 | 必填 | 描述                   |
| ------- | -------- | ------ | ---- | ---------------------- |
| success | function |        | 否   | 回调成功 |
| fail    | function |        | 否   | 回调失败 |


#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 是否必填 | 描述                     |
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
syber.webview.reload({
  success:function(result){
    console.log('success',result); 
  },
  fail:function(error){
    console.log('fail: ', error.code, error.msg);
  }
})
```

## syber.webview.goBack()

返回

### 参数

#### Object object

| 属性    | 类型     | 默认值 | 必填 | 描述                   |
| ------- | -------- | ------ | ---- | ---------------------- |
| success | function |        | 否   | 回调成功 |
| fail    | function |        | 否   | 回调失败 |


#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 是否必填 | 描述                     |
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
syber.webview.goBack({
  success:function(result){
    console.log('success',result); 
  },
  fail:function(error){
    console.log('fail: ', error.code, error.msg);
  }
})
```

## syber.webview.redirectTo(Object object)


跳转到某个地址

### 参数
#### Object object
| 属性    | 类型     | 默认值 | 必填 | 描述                   |
| ------- | -------- | ------ | ---- | ---------------------- |
| url     | string   |        | 是   | url地址          |
| success | function |        | 否   | 回调成功 |
| fail    | function |        | 否   | 回调失败 |


#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 是否必填 | 描述                     |
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
syber.webview.redirectTo({
  url:'https://baidu.com',
  success:function(result){
    console.log('success',result); 
  },
  fail:function(error){
    console.log('fail: ', error.code, error.msg);
  }
})
```
