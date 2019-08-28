---
title: API 说明
---

> API 的封装在陆续进行中， 有时候难免有些 API 没有加入，你可以通过提 PR 或者 issue，来获得帮助。

SyberOS-Hybrid 的 API 是对原生功能调用的 API 的封装。

API 调用关乎着整个体验，我们约定所有 API 统一采用如下调用方式

```js
syber.模块名.方法({
    参数1: "",
    参数2: "",
    success: fucntion(result) {
        // 成功回调
    },
    fail: fucntion(error) {
        // 失败回调
    }
});
```

代码示例

```javascript
syber.modal.alert({
    content: 'This is a alert',
    success: fucntion() {
        console.log('success');
    },
    fail: fucntion(error) {
        console.log('fail: ', error.code, error.msg);
    }
  })
```

<!-- 同时，为了方便代码书写，API 进行了 `promisify` 化，你可以像使用 Promise 那样进行调用，例如

``` javascript
syber.modal.alert({
    content: 'This is a alert',
  }).then(function() {
    console.log('success');
  }).catch(function(error) {
    console.log('fail: ', error.code, error.msg);
  })
```

> 因为规划 API 有长期 API 和短期 API 的区别,长期 API 暂时不支持`promise`,所以在使用中具体是否支持 `promise` 需要参见具体的 API 文档说明 -->
