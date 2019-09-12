---
title: getInfo
id: version-1.0.0-getInfo
original_id: getInfo
---

文件信息


## syberh.fileManager.getInfo(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| srcPath | String |  | 是| 源路径 |
| success | function |  |  否     |     |

### success 回调函数
Object类型，属性如下：

属性 | 类型 | 描述
---|---|---
path | String | 文件位置
size | number | 文件大小（字节）
created | String | yyyy-MM-dd hh:mm:ss

### 示例代码

```javascript
syberh.fileManager.getInfo({
    srcPath: '/home/user/22',
    success: function(res) {
        console.info(res)
    }
})
```

