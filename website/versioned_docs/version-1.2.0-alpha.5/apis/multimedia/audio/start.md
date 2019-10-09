---
title: start
id: version-1.2.0-alpha.5-start
original_id: start
---


开始播放语音：输入音频文件地址，对音频文件进行播放，也可以从指定的时间开始播放（默认从头开始播放）。


## syberh.audio.start(Object object)
### **参数**
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| path | string |        | 是       | 音频路径                           |
| position | int |    0    | 否       | 指定播放时间（秒）                  |
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

#### object.success回调函数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | 返回true, 表示执行成功  |

**object.fail回调函数**
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **代码示例**
``` javascript
syberh.audio.start({
  path: "/home/user/audio/xxx.aac",
	success: function(result){
    console.log('success', result);  
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
