---
title: saveImageToPhotosAlbum
id: version-1.1.1-alpha.3-saveImageToPhotosAlbum
original_id: saveImageToPhotosAlbum
---

## syberh.image.saveImageToPhotosAlbum(Object object)

保存图片到系统相册

### 参数

#### Object object

| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| filePath | String | 是 | 图片文件路径，不支持网络图片路径 |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |


#### object.success 回调函数参数

#### 参数
| 属性           | 类型    | 描述                                 |
| -------------- | ------  | ------------------------------------ |
| filePath | String | 保存到系统相册之后的图片路径 |

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.image.saveImageToPhotosAlbum({
    filePath:"myapp1://openPage",
	  success:function(result){
        console.log('filePath: ', result);
    }
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```