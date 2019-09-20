---
title: delRecorder
---


删除录音：可以对录音进行删除。


## syberh.audio.delRecorder(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| path | string |        | 是       | 录音路径                           |
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

#### object.success回调函数 
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| result | boolean  | 是     | 返回true, 表示执行成功  |

#### object.fail回调函数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### 代码示例
``` javascript
syberh.audio.delRecorder({
  path: "/home/user/audio/20190905_1567662466.aac",
	success: function(result){
    console.log('success',result);    
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
