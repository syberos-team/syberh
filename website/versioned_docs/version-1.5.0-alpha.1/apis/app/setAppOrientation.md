---
title: 全局配置
id: version-1.5.0-alpha.1-setAppOrientation
original_id: setAppOrientation
---

## syberh.app.setAppOrientation(Object object)

设置当前应用的屏幕旋转，[相关订阅事件](/docs/global-event.html#onresize)

### 参数
#### Object object
| 属性    | 类型     | 默认值 | 必填 | 描述                   |
| ------- | -------- | ------ | ---- | ---------------------- |
|orientation|number|0|否| 屏幕旋转方向(0: 自动旋转，1：竖屏， 2：横屏， 8：横屏反向)
| success | function |        | 否   | 回调成功 |
| fail    | function |        | 否   | 回调失败 |


#### object.success 回调函数参数
#### Object object
#### 参数
| 属性     | 类型    | 必填 | 描述                     |
| ---------- | ------- | -------- | ---------------------- |
| pageOrientation | number  | 是     | 当前页面的方向(0: 自动旋转，1：竖屏， 2：横屏， 8：横屏反向)  |
| appOrientation | number  | 是     | 当前应用的方向(0: 自动旋转，1：竖屏， 2：横屏， 8：横屏反向)  |

#### object.fail 回调函数
#### Object object
#### 参数
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 代码示例
``` javascript
syberh.app.setAppOrientation({
    orientation: 2,
    success: function (result) {
        console.log('应用旋转成功', JSON.stringify(result))
    },
    fail: function (error) {
        console.log('应用旋转失败', error.code, error.msg)
        showTips(JSON.stringify(error))
    }
});
```