---
title: startAudioRecorder
---


开始录音：对周围环境的声音进行记录，开启成功则返录音路径。


## syberh.audio.startAudioRecorder()
### **参数**
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

**object.success回调函数**
#### 参数
| 属性 | 类型   | 描述         |
| ---- | ------ | ------------ |
| path | String | 录音路径 |

**object.fail回调函数**
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **代码示例**
``` javascript
syberh.audio.startAudioRecorder({
	success: function(result){
		console.log('success: ', result.path); 
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
