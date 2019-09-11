---
title: move
---

文件移动


## syber.fileManager.move(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| srcPath | String |  | 是| 源路径 |
| destPath | String |  | 是 |目标路径 |
| success | function |  |  否     | 回调（true/false）      |



### 示例代码

```javascript
syber.fileManager.move({
    srcPath: '/home/user/22',
    destPath: '/home/user/222',
    success: function(res) {
        console.info(res)
    }
})
```

