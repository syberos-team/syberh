---
title: openDocument
id: version-1.1.1-alpha.3-openDocument
original_id: openDocument
---

## syberh.package.openDocument(Object object)

唤起应用，如果path传值了，就打开对应页面，然后处理参数，如果path为空，则在当前页面处理

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

> 元心系统支持沙盒机制，即：每个应用都有自己对应的沙盒，每个应用程序之间不能相互访问非本程序的沙盒<br/>
> 如果想跨应用处理文件，则需要给filePath传值，然后此接口会将应用唤起，并将该文件拷贝到被唤起应用的沙盒内。
> 注：文件拷贝功能暂时不能用

#### object.success 回调函数参数
值
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
syberh.package.openDocument({
    sopid:"com.syberh.myaap1",
    uiappid:"myaap1",
    action:"openPage",
    path:"second.html?name=zhangsan",
    params:{
        mimeType:"*/*",
        filePath:"/data/data/com.syberh.myaap1/test.txt",
              
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

> 被唤起应用示例放到了git上，地址：https://github.com/talicoasdf/myapp1

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