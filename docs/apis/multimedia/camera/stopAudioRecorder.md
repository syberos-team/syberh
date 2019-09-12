---
title: stopAudioRecorder
---


结束录音：对录音功能进行停止。


## syberh.audio.stopAudioRecorder()
### **参数**
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

**object.fail回调函数**
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **代码示例**
``` javascript
syberh.audio.stopAudioRecorder({
	success: function(result){
		console.log('success');
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
