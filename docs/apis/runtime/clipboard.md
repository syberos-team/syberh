---
title: 剪贴板
---


# clipboard

用于获取、设置剪切板内容，目前只支持字符串类型

## setString(text)
向系统剪贴板设置内容

### 参数
| 参数名 | 类型   | 是否必填 | 描述                   |
| ------ | ------ | -------- | ---------------------- |
| text   | String | 是       | 向系统剪贴板设置的内容 |

### 示例
```js
syber.clipboard.setString('some of the content');
```


## getString(callback)
从系统剪贴板获取内容

### 参数
| 参数名   | 类型     | 是否必填 | 描述     |
| -------- | -------- | -------- | -------- |
| callback | function | 否       | 回调函数 |

**回调函数参数**

| 类型   | 是否必填 | 描述                 |
| ------ | -------- | -------------------- |
| String | 否       | 从系统剪贴板获取内容 |

### 示例

```js
syber.clipboard.getString(function(data){
	console.log('content: ', data);
});
```

