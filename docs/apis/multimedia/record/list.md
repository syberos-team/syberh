---
title: list
---


录音列表：显示录音文件夹下的所有AAC格式录音记录。


## syberh.record.list()
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

#### object.success回调函数
#### 参数
| 属性 | 类型   | 描述         |
| ---- | ------ | ------------ |
| fileName | String | 录音名称 |
| path | String | 录音路径 |
| size | number | 录音大小 |
| duration | String | 录音时长(微秒) |
| created | String | 创建时间(yyyy-MM-dd hh:mm:ss) |

#### object.fail回调函数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **代码示例**
``` javascript
syberh.record.list({
	success: function(result){
      for(i = 0; i < result.length; i++) {
        console.log('success'，result[i].fileName，result[i].path，result[i].size，result[i].duration,result[i].created);    
      }
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
