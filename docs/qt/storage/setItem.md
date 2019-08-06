---
title: setItem
---

该方法可以通过键值对的形式将数据存储到本地。同时可以通过该方法，更新已有的数据。

### void setItem(QString callbackId, QString key, QVariant value)

### 信号
### void success(long responseID, bool result)
- responseID:	回调ID，用于标识每一次的调用
- result:  返回给页面用的，默认为true