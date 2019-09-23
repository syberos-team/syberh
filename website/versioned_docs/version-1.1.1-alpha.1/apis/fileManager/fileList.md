---
title: fileList
id: version-1.1.1-alpha.1-fileList
original_id: fileList
---

文件列表


## syberh.fileManager.fileList(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| srcPath | String |  | 是| 源路径 |
| success | function |  |  否     |       |

#### success 回调函数
回调的参数是Array类型，属性如下：

属性 | 类型 | 描述
---|---|---
path | String | 文件位置|
size | number | 文件大小（字节）|
created | String | yyyy-MM-dd hh:mm:ss|
isDir | boolean | | ture:文件夹 false:文件

### 示例代码

```javascript
syberh.fileManager.fileList({
    srcPath: '/home/user/22',
    success: function(res) {
        for(i = 0; i < res.length; i++) {
            console.info(res[i].path)
            console.info(res[i].size)
            console.info(res[i].created)
            console.info(res[i].isDir)
        }
    }
})
```

