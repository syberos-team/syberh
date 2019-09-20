---
title: openDocument
---

## syberh.package.openDocument(Object object)

唤起应用，打开如果path传值了，就打开对应页面，然后处理参数，如果path为空，则在当前页面处理

此功能需要在被唤起应用的sopconfig.xml中配置doctype [具体配置](../../app-config.html#doctype)

### 参数

#### Object object

| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| sopid | String | 是 | sopid [具体配置](../../app-config.html#sopconfig) |
| uiappid | String | 是 | uiappid [具体配置](../../app-config.html#uiapp) |
| action | String | 是 | 应用可以执行的操作，值：openPage，其余值可参见[具体配置](../../app-config.html#doctype) |
| path | String | 否 | 跳转的页面路径，如果为空则不跳转 |
| param | Object | 否 | 打开文档的参数 |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |

#### object.param 参数

| 属性     | 类型   | 必填 | 描述                                                     |
| -------- | ------ | ---- | -------------------------------------------------------- |
| mimeType | String | 否   | 文件内容类型，默认值*，[具体配置](../../app-config.html#doctype) |
| filePath | String | 否   | 文件路径                                                 |

```
参数可以自由扩展。以上参数如需打开文档时候传入
```

#### object.success 回调函数参数

#### 参数
| 属性           | 类型    | 描述                                 |
| -------------- | ------  | ------------------------------------ |
| result | String | 返回 success, 表示唤起成功 |

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.package.openDocument({
    sopid:"com.syberos.demo",
    uiappid:"app",
    action:"openPage",
    path:"index.html?name=zhangsan",
    params:{
        mimeType:"*/*",
        filePath:"test.txt",
        age:18,
        sex:'male'
    },
	success:function(result){
      console.log('result: ', result);
    }
    fail:function(error){
      console.log('fail: ', error.code, error.msg);
    }
});
```

### 应用被唤起回调

#### 参数

| 属性    | 类型   | 描述     |
| ------- | ------ | -------- |
| onShow | String | 固定值   |
| result  | Object | 回调结果 |

#### result 回调函数参数

#### 参数

| 属性  | 类型   | 描述                                               |
| ----- | ------ | -------------------------------------------------- |
| path  | String | 跳转的页面路径，index.html?key1=value1&key2=value2 |
| param | Object | 传递的参数，{key1=value1, key2=value2}格式         |

```
syberh.subscribe('onShow', function(result) {
  console.log("path: "+ result.path);
  console.log("params: "+ JSON.stringify(result.params));
});
```