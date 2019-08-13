---
title: getResolution
---

## syber.system.getResolution(Object object)

获取手机分辨率，支持Promise调用

### 参数

**Object object**

| 属性    | 类型     | 是否必填 | 描述                   |
| ------- | -------- | -------- | ---------------------- |
| success | function | 否       | 接口调用成功的回调函数 |
| fail    | function | 否       | 接口调用失败的回调函数 |

**object.success 回调函数参数**

**Object object**

| 参数名 | 类型   | 是否必填 | 描述 |
| ------ | ------ | -------- | ---- |
| height | number | 是       | 高度 |
| width  | number | 是       | 宽度 |

**object.fail回调函数参数**

**Object object**

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |

### 示例

```
syber.system.getResolution({
	success:function(result){
        console.log('height: ', result.height);
        console.log('width: ', result.width);
    }
    fail:function(error){
        console.log('code: ', error.code);
    	console.log('msg: ', error.msg);
    }
});

syber.system.getResolution().then(function(result) {
    console.log('height: ', result.height);
    console.log('width: ', result.width);
}).catch(function(error) {
    console.log('code: ', error.code);
    console.log('msg: ', error.msg);
});
```
