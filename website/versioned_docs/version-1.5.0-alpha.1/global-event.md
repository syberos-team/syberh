---
title: 订阅事件
id: version-1.5.0-alpha.1-global-event
original_id: global-event
---

目前syberh提供`onResize`订阅事件，后续事件正在开发中

## onResize

屏幕旋转的订阅事件，在[全局配置](apis/app/setAppOrientation.html)或者[路由](apis/router/router.html)里面相关API会触发

#### object result 回调函数参数
#### 参数
| 属性     | 类型  | 描述                         |
| ---------- | ------- | ----------------------------------
| pageOrientation | number  | 当前页面的方向(0: 自动旋转，1：竖屏， 2：横屏， 8：横屏反向)  |
| appOrientation | number  | 当前应用的方向(0: 自动旋转，1：竖屏， 2：横屏， 8：横屏反向)  |


### 代码示例
``` javascript
syberh.subscribe('onResize', function (result) {
    console.log("收到屏幕旋转消息: ", JSON.stringify(result));
});
```