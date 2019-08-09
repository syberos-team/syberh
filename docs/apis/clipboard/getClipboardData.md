---
title: getClipboardData
---


## syber.clipboard.getClipboardData(Object object)
获取系统剪贴板的内容 ,支持 `promise`调用

### 参数

**Object object**

| 属性    | 类型     | 是否必填 | 描述                   |
| ------- | -------- | -------- | ---------------------- |
| success | function | 否       | 接口调用成功的回调函数 |
| fail    | function | 否       | 接口调用失败的回调函数 |

#### object.success 回调函数

**String result**

| 属性 | 类型   | 描述         |
| ---- | ------ | ------------ |
| data | String | 剪贴板的内容 |

**object.fail回调函数参数**

**Object object**

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |

### 示例

```js
syber.clipboard.getClipboardData({
	success:function(result){
        console.log('content: ', result.data);
    }
    fail:function(error){
        console.log('code: ', error.code);
    	console.log('msg: ', error.msg);
    }
});

//promise
syber.clipboard.getClipboardData().then(function(result) {
    console.log('content: ', result.data);
}).catch(function(error) {
    console.log('code: ', error.code);
    console.log('msg: ', error.msg);
});
```

