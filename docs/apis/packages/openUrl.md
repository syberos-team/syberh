---
title: openUrl
---

## syberh.packages.openUrl(Object object)

唤起应用

> 默认打开第二个应用的`index.html`, 不可修改, 如有需要跳转其他页面的, 可自行跳转

### 参数

#### Object object

| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| scheme | String | 是 | 协议，格式为：scheme://openPage<br />scheme [具体配置](../../app-permissions.html#url) |
| param | Object | 否 | params中的参数会拼接到path中?后面。<br />目标APP可在 `syberh.subscribe` 中获取到这份数据 |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |

```
最终参数会拼接成：scheme://openPage/index.html?key=value&key=value格式，去唤起应用
```

#### object.success 回调函数参数

#### 参数
| 属性           | 类型    | 描述                                 |
| -------------- | ------  | ------------------------------------ |
| result | String | 返回 success, 表示已执行唤起 |

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.packages.openUrl({
    scheme:"myapp1://openPage",
    param:{
        age:18,
        sex:'male'
    },
	success:function(result){
        console.log('result: ', result);
    },
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```

> 被唤起应用示例放到了git上，地址：https://github.com/syberos-team/myapp1

### 应用被唤起回调

#### 参数

| 属性    | 类型   | 描述     |
| ------- | ------ | -------- |
| onReady | String | 固定值   |
| result  | Object | 回调结果 |

#### result 回调函数参数

#### 参数

| 属性  | 类型   | 描述                                               |
| ----- | ------ | -------------------------------------------------- |
| path  | String | 跳转的页面路径，index.html?key1=value1&key2=value2 |
| params | Object | 传递的参数，{key1=value1, key2=value2}格式         |

```js
syberh.subscribe('onReady', function(result) {
	console.log("path: "+ result.path);
	console.log("params: "+ JSON.stringify(result.params));
});
```
