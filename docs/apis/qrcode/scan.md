---
title: qrcode
---

扫码，可以扫二维码和条形码
> S1手机上运行扫码功能，需要下载单独的模块


## syberh.qrcode.scan(Object object)
### 参数
#### Object object
| 属性     | 类型   | 默认值  |  必填 | 描述                         |
| ---------- | ------- | -------- | ---------------- | ----------------------------------
| success | function |  |  否     |     |

#### object.success 回调函数参数
#### 参数
#### Object object
| 属性   | 类型    | 必填 | 描述                    |
| ------ | ------- | ---- | ----------------------- |
| result | String | 是   |  |


#### object.error回调函数
#### 参数
#### Object Object
| 属性 | 类型  | 描述 |
| -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |

### 示例代码

```javascript
syberh.qrcode.scan({
    success: function (result) {
        console.log('syberh.qrcode.scan success', result.result)
    },
    error: function (error) {
        console.log('syberh.qrcode.scan error', error.code, error.msg)
    }
})
```

## 在S1手机上运行扫码
1、在项目根目录下的`platforms/syberos/vendor`下删除`syberh-qrcode`文件夹

2、在项目根目录下的`platforms/syberos/vendor`下,下载S1手机扫码模块
```javascript
git clone -b s1 https://github.com/syberos-team/syberh-qrcode
```
