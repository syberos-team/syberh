---
title: confirm
---

### void confirm(QString callbackId, QVariant options)
### 参数
| 参数名 | 说明 | 类型 | 默认值 |
| -- | -- | -- | -- |
| title | 标题 | QString | -
| message | 内容 | QString | -
| okTitle | 确认按钮上显示的文字信息 | QString | 确认 | 
| cancelTitle | 确认按钮上显示的文字信息 | QString | 取消 |

### 信号
### void success(long responseID, QVariant result)
- responseID:	回调ID，用于标识每一次的调用
- result:  返回给页面用的
    result: QString 用户按下的按钮上的文字信息

