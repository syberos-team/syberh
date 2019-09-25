---
title: getImageInfo
---


图片信息：获取图片的详细信息。


## syberh.record.getImageInfo(Object object)
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------|
| path | string |        | 是       | 图片路径                           |
| success | function |        | 否       | 回调成功                    |
| fail   | function |        | 否       | 回调失败                    |

**object.success回调函数**
#### 参数
| 属性 | 类型   | 描述         |
| ---- | ------ | ------------ |
| fileName | String | 名称 |
| width | String | 宽度 |
| height | String | 高度 |
| type | String | 类型 |
| size | number | 大小 |
| created | String | 创建时间(yyyy-MM-dd hh:mm:ss) |

**object.fail回调函数**
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误消息 |



### **代码示例**
``` javascript
syberh.image.getImageInfo({
	success: function(result){
    console.log('success'，result[i].fileName，result[i].width，result[i].height，result[i].type，result[i].size,result[i].created);    
      
	},
	fail: function(error){
		console.log('fail: ', error.code, error.msg);
	}
});
```
