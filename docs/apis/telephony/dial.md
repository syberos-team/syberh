---
title: dial
---

## syber.telephony.dial(Object object)

拨号

### 参数

**Object object**

| 属性    | 类型     | 是否必填         | 描述     |
| ------- | -------- | ---------------- | -------- |
| tel     | String   | 是 | 对方号码      |
| success | function | 否               | 回调函数 |
| fail   | function | 否               | 回调函数 |

#### success回调函数参数

**Object object**

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |

#### object.fail回调函数参数

**Object object**

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |

### 示例

```
syber.telephony.dial({
	tel: "150xxxxxxxx",
	success: function(result){
		console.log('code: ', result.code);
		console.log('msg: ', result.msg);
	},
	fail: function(error){
		console.log('code: ', error.code);
		console.log('msg: ', error.msg);
	}
});

syber.telephony.dial({
	tel: "150xxxxxxxx",
}).then(function(result) {
  console.log('code: ', result.code);
	console.log('msg: ', result.msg);
}).catch(function(fail) {
  console.log('code: ', fail.code);
	console.log('msg: ', fail.msg);
});
```

