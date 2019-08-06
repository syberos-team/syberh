---
title: removeItem
---

传入一个键名将会删除本地存储中对应的键值

### void removeItem(QString callbackId, QString key)

### 信号
### void success(long responseID, bool result)
- responseID:	回调ID，用于标识每一次的调用
- result:  返回给页面用的，默认为true