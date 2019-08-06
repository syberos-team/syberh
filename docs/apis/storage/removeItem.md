---
title: removeItem
---

传入一个键名将会删除本地存储中对应的键值

### removeItem(key, callback)

| 参数 | 说明 | 类型 |
| -- | -- | -- |
| key | 要存储的键，不允许是 "" 或 null | string
| callback | 执行操作成功后的回调 e.result：表示设置是否成功，如果成功返回 "success"  e.data：undefined 表示设置成功，invalid_param 表示 key/value 为 "" 或者 nulll | function(e) |