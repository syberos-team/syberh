---
title: dataRoot
---

应用数据路径


## syberh.path.dataRoot(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| success | function |  |  否     |     |

#### object.success 回调函数参数

#### 参数

| 属性   | 类型    | 必填 | 描述                    |
| ------ | ------- | ---- | ----------------------- |
| result | String | 是   |  |

### 示例代码

```javascript
syberh.path.dataRoot({
    success: function (res){
        syberh.modal.alert({content: res.result});
    }
})
```

