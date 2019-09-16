---
title: startPlay
id: version-1.1.0-startPlay
original_id: startPlay
---


播放录音：可以对录音记录进行播放。


## syberh.audio.startPlay(Object object)
### **参数**
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| path | string |        | 是       | 录音路径                           |
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
syberh.audio.startPlay({
  path: "/home/user/audio/20190905_1567662466.aac",
	success: function(result){
    console.log('success');    
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
