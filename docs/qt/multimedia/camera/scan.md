---
title: 扫码
---

# 概况

<span class="arg-name">barcode</span> 模块管理条码（一维码和二维码）扫描识别，目前仅支持二维码（QR）。
通过调用摄像头对条码进行扫描识别，扫描到条码后进行解码并返回码数据内容及码类型。



## scan

扫描二维码，成功则返回条码类型及内容



**参数**

| 参数名     | 类型    | 是否必填 | 描述                                      |
| ---------- | ------- | -------- | ----------------------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用              |
| camera     | long    | 是       | 指定摄像头，`1` ：主摄像头，`2`：辅摄像头 |

**示例代码**

```
void scan(QString callbackId,long camera);
```



**成功信号**

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | long    | 是       | 回调ID，用于标识每一次的调用 |
| result     | QString | 是       |                              |

result:

| 参数名  | 类型    | 是否必填 | 描述         |
| ------- | ------- | -------- | ------------ |
| type    | QString | 是       | 二维码的类型 |
| content | QString | 是       | 二维码的内容 |



**示例代码**

```
emit success(long responseID, QVariant result);
```

```
result：
{
	type: "video",
    content: "二维码内容"
}
```





## 失败信号

**参数**

| 参数名     | 类型    | 是否必填 | 描述                         |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | long    | 是       | 回调ID，用于标识每一次的调用 |
| code       | long    | 是       | 错误码                       |
| msg        | QString | 是       | 错误信息                     |

**示例代码**

```
emit failed(long responseID, long code, QString msg);
```

```
{
	code: 500,
    msg: "系统错误"
}
```

