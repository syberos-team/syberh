---
title: start
id: version-1.4.0-alpha.1-start
original_id: start
---


开始录音：对周围环境的声音进行录制，开启成功则返录音路径。录音文件为AAC格式。

> 录音功能属于敏感权限,要实现录音必须获取录音权限以及数据存储权限,在sopconfig.xml文件中添加如下字段:

``` javascript
<uses-permission syberos:name="syberos.permission.RECORD"/>
<uses-permission syberos:name="syberos.permission.ACCESS_STORAGE"/>
```

## syberh.record.start()
### **参数**
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

#### object.success回调函数
#### 参数
| 属性 | 类型   | 描述         |
| ---- | ------ | ------------ |
| path | String | 录音路径 |

#### object.fail回调函数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **代码示例**
``` javascript
syberh.record.start({
	success: function(result){
		console.log('success: ', result.path); 
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
