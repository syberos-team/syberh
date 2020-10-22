---
title: previewImage
---

在新页面中全屏预览图片。

<!-- 支持`Promise` 使用。 -->


## syberh.image.previewImage(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------------ | -------- | :------: | ------------ |
| urls | Array.<string> |  | 是 | 需要预览的图片链接列表 |
| current | string |  	urls 的第一张  | 是 | 当前显示图片的链接 |
| success | function |  |  否     | 回调成功      |
| fail   | function |  |  否     | 回调失败      |

#### object.fail 回调函数
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
```javascript
syberh.image.previewImage({
    current: '',
    urls: [],
    success: function () {
        console.log('image.previewImage success')
    },
    fail: function(error) {
        console.log('image.previewImage fail: ', error.code, error.msg)
    }
})
```