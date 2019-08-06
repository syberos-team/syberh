---
title: getItem
---

传入键名返回对应的键值。

### getItem(QString callbackId, QString key)

### 信号
### void success(long responseID, QVariant result)
- responseID:	回调ID，用于标识每一次的调用
- result: 
    + result: QVariant 返回对应的键值