---
title: remove
---

文件删除


## syberh.fileManager.remove(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| srcPath | String |  | 是| 源路径 |
| recursive | int |  | 是 | 递归删除 0：否，1：是 |
| success | function |  |  否     |    |

#### object.success 回调函数参数

#### 参数

| 属性   | 类型    | 必填 | 描述                    |
| ------ | ------- | ---- | ----------------------- |
| result | boolean | 是   | 返回 true, 表示执行成功 |

### 示例代码

```javascript
syberh.fileManager.remove({
    srcPath: '/home/user/22',
    recursive: 0,
    success: function(res) {
        console.info(res)
    }
})
```

