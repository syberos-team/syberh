---
title: filepicker
---

文件选择，支持筛选特定类型的文件，选择文件成功后则返回文件路径

> filepicker 为 syberos 中自带的文件选择功能

## syberh.filepicker.open(Object object)

### **参数**

#### Object object

| 属性     | 类型     | 默认值 | 必填 | 描述               |
| -------- | -------- | :----: | ---- | ------------------ |
| count    | number   |    1   | 否   | 最多可以选择的文件个数 |
| title    | string   |        | 否   | 标题               |
| showBack | boolean  | false  | 否   | 是否显示返回按钮   |
| category | string   |        | 否   | 需要展示的文件类型 |
| success  | function |        | 否   | 回调成功           |
| fail     | function |        | 否   | 回调失败           |

#### object.category 的合法值

| 值       | 说明                           |
| -------- | ------------------------------ |
| image    | 所有图像文件                   |
| video    | 所有视频文件                   |
| audio    | 所有音频文件                   |
| document | 所有文档文件                   |
| text     | 所有纯文本文件(包括 HTML 文件) |

**object.success 回调函数**

#### 参数

| 属性    | 类型    | 描述               |
| ------- | ------- | ------------------ |
| files    | string  | 返回选择的文件的对象数组 |

**object.fail 回调函数**

#### 参数

| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | string | 错误码   |
| msg  | string | 错误消息 |

### **代码示例**

```javascript
syberh.filepicker.open({
  title: '照片选择',
  showBack: true,
  category: 'image',
  count: 2,
  success: function(result) {
    if (result && result.files) {
      console.log(JSON.stringify(result.files))
    }
  },
  fail: function(error) {
    console.log('filepicker open fail')
  }
})
```
