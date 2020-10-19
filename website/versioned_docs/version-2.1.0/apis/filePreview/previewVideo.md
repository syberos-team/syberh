---
title: previewVideo
id: version-2.1.0-previewVideo
original_id: previewVideo
---

预览指定的视频文件

## syberh.filePreview.previewVideo(Object object)

### **参数**

#### Object object

| 属性     | 类型     | 默认值 | 必填 | 描述               |
| -------- | -------- | :----: | ---- | ------------------ |
| path     | string   |        | 否   | 文件路径               |
| success  | function |        | 否   | 回调成功           |
| fail     | function |        | 否   | 回调失败           |


**object.success 回调函数**

无回调参数


**object.fail 回调函数**

#### 参数

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | string | 错误码   |
| msg  | string | 错误消息 |

### **代码示例**

```javascript
syberh.filePreview.previewVideo({
  path: '/home/user/1.mp4',
  success: function() {
    console.log('preview success');
  },
  fail: function(error) {
    console.log('preview failed')
  }
})
```
