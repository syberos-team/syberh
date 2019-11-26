---
title: 生命周期
id: version-1.4.1-started-lifecycle
original_id: started-lifecycle
---

目前syberh提供onShow订阅事件，后续事件正在开发中

## onShow

使用 [路由](apis/router/router.html) 打开新页面或者当前页返回上一张页面时触发

### 参数
#### Object result
| 属性     | 类型  | 描述                         |
| ---------- | ------- | ----------------------------------
| status | String | 表示当前页面的状态      |

#### result.status
| 值 | 类型  | 描述                     |
| -- | -- | ---------------------- |
| ready | String | 打开新页面完成 |
| redisplay | String | 由后一页面返回当前页 |


### 代码示例
``` javascript
syberh.subscribe('onShow', function (result) {
  // 打印 result: ready 1574414494470
  console.log("result: ", result.status, new Date().getTime());
});
```

