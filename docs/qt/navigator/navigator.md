---
title: navigator
---

导航栏组件，主要用于头部导航。 C++实现

### void navigator(QString callbackId, QVariant options)

### 参数
| 属性名 | 说明 | 类型 | 默认值 |
| -- | -- | -- | -- |
| titleText | 标题文字 | QString | '' |
| leftItemText | 左边文字 | QString | '' |
| leftItemIcon | 左边图标 | QString | '' |
| rightFirstIcon | 从右到左，第一个图标 | QString | -
| rightSecondIcon | 从右到左，第二个图标 | QString | -


### 信号
### void success(long responseID, QString result)
- responseID:	回调ID，用于标识每一次的调用
- result:   "0"是左边第一个图标类型点击事件, "1"是从右到左第一个图标类型点击事件, "2"是从右到左第二个图标类型点击事件