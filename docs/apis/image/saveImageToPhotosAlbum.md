---
title: saveImageToPhotosAlbum
---

## syberh.image.saveImageToPhotosAlbum(Object object)

保存图片到手机

### 参数

#### Object object

| 属性    | 类型     | 必填 | 描述                                                         | 最低版本|
| ------- | -------- | -------- | ------------------------------------------------------------ |----|
| filePath | String | 否 | 图片文件路径，不支持网络图片路径 | |
| data | String | 否 | base64格式的图片 | 2.1.2 |
| name | String | 否 | 文件名 | 2.1.2 |
| path | String | 否 | 要保存的目录(默认保存到相册) | 2.1.2 |
| isCover | boolean | 否 | 是否覆盖(默认不覆盖) | 2.1.2 |
| success | function | 否       | 成功回调                                       | |
| fail    | function | 否       | 失败回调                                       | |


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
// 保存图片文件
syberh.image.saveImageToPhotosAlbum({
    filePath: "/home/user/a.jpg",
	success: function(result) {
        console.log('filePath: ', result);
    },
    fail: function(error) {
        console.log('fail: ', error.code, error.msg);
    }
});

// 保存base64图片
syberh.image.saveImageToPhotosAlbum({
    // base64 图片长这个样子
    data: 'data:image/jpeg;base64,/9j/4A......',
    name: 'b.jpg',
    path: '/home/user',
    isCover: true,
    success: function (result) {
        console.log('filePath: ', result);
    },
    fail: function (error) {
        console.log('fail: ', error.code, error.msg);
    }
});
```