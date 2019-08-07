---
title: aboutPhone
---

## syber.systeminfo.aboutPhone(Object object)

获取手机信息，支持Promise调用

### 参数

**Object object**

| 属性    | 类型     | 是否必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| modem   | number   | 否       | 在双卡平台可用，默认为0，<br />0：取第一个modem的imei<br />1：取第二个modem的imei |
| success | function | 否       | 接口调用成功的回调函数                                       |
| error   | function | 否       | 接口调用失败的回调函数                                       |

**object.success 回调函数参数**

**Object object**

| 属性           | 类型   | 描述                                 |
| -------------- | ------ | ------------------------------------ |
| id             | String | 编号                                 |
| name           | String | 手机名字                             |
| imei           | String | 移动设备国际识别码                   |
| simCardNumbers | Array  | 如果是双卡，有多个手机号             |
| imsis          | Array  | 如果是双卡，有多个国际移动用户识别码 |

**object.error回调函数参数**

**Object object**

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |

### 示例
```js
syber.systeminfo.aboutPhone({
    modem: 0,
	success:function(result){
        console.log('id: ', result.id);
        console.log('name: ', result.name);
        console.log('imei: ', result.imei);
        console.log('simCardNumbers: ', result.simCardNumbers);
        console.log('imsis: ', result.imsis);
    }
    error:function(error){
        console.log('code: ', error.code);
    	console.log('msg: ', error.msg);
    }
});

syber.systeminfo.aboutPhone({
    modem: 0,
}).then(function(result) {
    console.log('id: ', result.id);
    console.log('name: ', result.name);
    console.log('imei: ', result.imei);
    console.log('simCardNumbers: ', result.simCardNumbers);
    console.log('imsis: ', result.imsis);
}).catch(function(error) {
    console.log('code: ', error.code);
    console.log('msg: ', error.msg);
});
```
