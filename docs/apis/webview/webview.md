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
| success | function |        | 否   | 接口调用成功的回调函数 |
| fail    | function |        | 否   | 接口调用失败的回调函数 |

### 代码示例

```
syber.webview.reload({
  success:function(res){
    console.log(res)
  },
  fail:function(error){
    console.log(error)
  }
})
```

## syber.webview.goBack()

返回

### 参数

#### Object object

| 属性    | 类型     | 默认值 | 必填 | 描述                   |
| ------- | -------- | ------ | ---- | ---------------------- |
| success | function |        | 否   | 接口调用成功的回调函数 |
| fail    | function |        | 否   | 接口调用失败的回调函数 |

### 代码示例

```
syber.webview.goBack({
  success:function(res){
    console.log(res)
  },
  fail:function(error){
    console.log(error)
  }
})
```

## syber.webview.redirectTo(Object object)

跳转到某个地址

### 参数

#### Object object

| 属性    | 类型     | 默认值 | 必填 | 描述                   |
| ------- | -------- | ------ | ---- | ---------------------- |
| url     | string   |        | 是   | 打开 url 地址          |
| success | function |        | 否   | 接口调用成功的回调函数 |
| fail    | function |        | 否   | 接口调用失败的回调函数 |

### 代码示例

```
syber.webview.redirectTo({
  url:'https://baidu.com',
  success:function(res){
    console.log(res)
  },
  fail:function(error){
    console.log(error)
  }
})
```
