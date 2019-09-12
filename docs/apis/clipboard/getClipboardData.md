---
title: getClipboardData
---

获取系统剪贴板的内容 

<!-- 支持`Promise` 使用。 -->

## syberh.clipboard.getClipboardData(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| success | function |  |  是       | 回调成功      |
| fail   | function |  |  是       | 回调失败      |

#### object.success 回调函数参数
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| data | String |   |剪贴板的内容 |

#### object.fail 回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |


### 代码示例
``` javascript
syberh.clipboard.getClipboardData({
	success:function(result){
        console.log('success: ', result.data);
    },
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```

<!-- #### Promise
``` javascript
syberh.clipboard.getClipboardData()
    .then(function(result) {
        console.log('success: ', result.data);
    }).catch(function(error) {
        console.log('fail: ', error.code, error.msg);
    });
``` -->

