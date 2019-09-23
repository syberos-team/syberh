---
title: recorderList
id: version-1.1.1-alpha.2-recorderList
original_id: recorderList
---


录音列表：显示录音文件夹下的所有AAC格式录音记录。


## syberh.record.recorderList()
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

**object.success回调函数**
#### 参数
| 属性 | 类型   | 描述         |
| ---- | ------ | ------------ |
| path | String | 录音路径 |
| size | number | 录音大小 |
| time | number | 录音时长 |
| created | String | 创建时间 |

**object.fail回调函数**
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **代码示例**
``` javascript
syberh.record.recorderList({
	success: function(result){
      for(i = 0; i < result.length; i++) {
        console.log('success'，result[i].path，result[i].size，result[i].time,result[i].created);    
      }
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
