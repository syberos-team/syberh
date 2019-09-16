---
title: request
id: version-1.1.0-request-c
original_id: request-c
---

### void request(QString callBackID, QVariantMap params)
> 发起网络请求

### 参数
属性 | 类型 | 必填 | 描述
---|---|---|---
callBackID| QString | 是 | 请求的唯一标志,用于应用判断是否为自己发送的请求
params| QVariantMap | 是 | 请求传递的参数

### 示例
```C++
...
```

### 成功信号
### void sucess(long responseID,QVariant result)
### 参数
属性 | 类型 | 必填 | 描述
---|---|---|---
responseID | long | 是 | 请求传入的唯一标志，用于应用判断是否为自己发送的请求
result| QVariant | 是 | 请求结果

### 失败信号
### void failed(long responseID,long errorCode,QString errorMsg)
### 参数
属性 | 类型 | 必填 | 描述
---|---|---|---
responseID | long | 是 | 请求传入的唯一标志，用于应用判断是否为自己发送的请求
errorCode| long | 是 | 错误码
errorMsg| QString | 是 | 错误信息