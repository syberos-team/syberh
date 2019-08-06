---
title: getString
---


## syber.clipboard.getString(Object object)
从系统剪贴板获取内容，支持Promise调用

### 参数

**Object object**

| 属性    | 类型     | 是否必填 | 描述                   |
| ------- | -------- | -------- | ---------------------- |
| success | function | 否       | 接口调用成功的回调函数 |
| error   | function | 否       | 接口调用失败的回调函数 |

**object.success 回调函数参数**

**String result**

| 属性   | 类型   | 描述                 |
| ------ | ------ | -------------------- |
| result | String | 从系统剪贴板获取内容 |

**object.error回调函数参数**

**Object object**

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |

### 示例

```js
syber.clipboard.getString({
	success:function(result){
        console.log('content: ', result);
    }
    error:function(error){
        console.log('code: ', error.code);
    	console.log('msg: ', error.msg);
    }
});

syber.clipboard.getString().then(function(result) {
    console.log('content: ', result);
}).catch(function(error) {
    console.log('code: ', error.code);
    console.log('msg: ', error.msg);
});
```

