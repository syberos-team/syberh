---
title: copy
id: version-1.0.0-copy
original_id: copy
---

文件复制


## syberh.fileManager.copy(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| srcPath | String |  | 是| 源路径 |
| destPath | String |  | 是 |目标路径 |
| success | function |  |  否     |     |

#### object.success 回调函数参数

#### 参数

| 属性   | 类型    | 必填 | 描述                    |
| ------ | ------- | ---- | ----------------------- |
| result | boolean | 是   | 返回 true, 表示执行成功 |

### 示例代码

```javascript
syberh.fileManager.copy({
    srcPath: '/home/user/22',
    destPath: '/home/user/222',
    success: function(res) {
        console.info(res)
    }
})
```

