---
title: select
---

从本地相册选择图片或使用相机拍照。

<!-- 支持`Promise` 使用。 -->


## syberh.image.select(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| count | number |  | 否 | 最多可以选择的图片张数 |
| sourceType | Array.<string> |  ['album', 'camera']  | 否 | 标题图标 |
| success | function |  |  否     | 回调成功      |
| fail   | function |  |  否     | 回调失败      |


#### object.sourceType 的合法值
| 值     | 说明    |       
| ---------- | ------- | 
| album | 从相册选图 |
| camera | 使用相机	 |


#### object.success 回调函数
#### 参数
#### Object res
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| tempFilePaths | 	Array.<string>   | 图片的本地文件路径列表 |
| tempFiles     |   Array.<Object>   | 图片的本地文件列表 |


#### res.tempFiles 的结构
#### 参数
#### Object res
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| path     | string | 本地文件路径 |
| size     | number | 本地文件大小，单位 B |

#### object.fail 回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
```javascript
syberh.image.select({
    count: count,
    sourceType: sourceType,
    success: function (res) {
        console.log('选择图片成功', res)
        // tempFilePath可以作为img标签的src属性显示图片
        var tempFilePaths = res.tempFilePaths
    },
    fail: function(error) {
        console.log('fail: ', error.code, error.msg)
    }
})
```