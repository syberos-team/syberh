---
title: move
id: version-1.1.1-alpha.3-move
original_id: move
---

文件移动


## syberh.fileManager.move(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| srcPath | String |  | 是| 源路径 |
| destPath | String |  | 是 |目标路径 |
| success | function |  |  否     | 回调成功      |
| fail   | function |  |  否     | 回调失败      |

#### object.success 回调函数参数

#### 参数

| 属性   | 类型    | 必填 | 描述                    |
| ------ | ------- | ---- | ----------------------- |
| result | boolean | 是   | 返回 true, 表示执行成功 |

#### object.fail回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 示例代码

```javascript
syberh.fileManager.move({
    srcPath: '/home/user/22',
    destPath: '/home/user/222',
    success: function(res) {
        console.info(res)
    },
    fail: function(error) {
        console.log(error)
    }
})
```

