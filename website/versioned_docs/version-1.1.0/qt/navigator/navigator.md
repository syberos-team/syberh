---
title: navigator
id: version-1.1.0-navigator
original_id: navigator
---

导航栏组件，主要用于头部导航。 C++实现

### void navigator(QString callbackId, QVariant options)
### 参数
| 参数名     | 类型    | 是否必填 | 描述                            |
| ---------- | ------- | -------- | ---------------------------- |
| callbackId | QString | 是       | 回调ID，用于标识每一次的调用      |
| titleText | QString  | 否      | 标题文字      |
| leftItemText | QString | 否       | 左边文字      |
| leftItemIcon | QString | 否       | 左边图标      |
| rightFirstIcon | QString | 否       | 从右到左，第一个图标      |
| rightSecondIcon | QString | 否       | 从右到左，第二个图标      |


### 信号
### void success(long responseID, QString result)
| 参数名     | 类型    | 是否必填 | 描述                            |
| ---------- | ------- | -------- | ---------------------------- |
| responseID | QString | 是       | 回调ID，用于标识每一次的调用      |
| result     | QString    | 是       |  "0"是左边第一个图标类型点击事件<br/>"1"是从右到左第一个图标类型点击事件<br/>"2"是从右到左第二个图标类型点击事件              |