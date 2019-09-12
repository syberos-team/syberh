---
title: navigator
id: version-1.0.0-navigator
original_id: navigator
---

导航栏组件，主要用于头部导航, 支持`Promise` 化使用

## syberh.navigator.setNavigator(Object object)
### 参数
#### Object object
| 属性     | 类型    | 是否必填 | 描述                            |
| ---------- | ------- | -------- | ---------------------------- |
| title | String  | 否      | 标题文字      |
| leftText | String | 否       | 左边文字      |
| leftIcon | String | 否       | 左边图标      |
| rightFirstIcon | String | 否       | 从右到左，第一个图标      |
| rightSecondIcon | String | 否       | 从右到左，第二个图标      |
| success         | function | 否       | 回调函数      |
| error         | function | 否       | 回调函数      |


#### object.success回调函数参数
#### 参数
#### Object res
| 属性     | 类型    | 是否必填 | 描述                            |
| ---------- | ------- | -------- | ---------------------------- |
| result | String  | 是     | 用户按下的类型 <br/> "0"是左边第一个图标类型点击事件 <br/>"1"是从右到左第一个图标类型点击事件<br/>"2"是从右到左第二个图标类型点击事件      |

#### object.error回调函数
#### 参数
#### Object error
| 属性 | 类型  | 描述 |
| -- | -- | -- | -- |
| code | String | 错误码 |
| msg | String  | 错误信息 |



### 代码示例
```javascript
    syberh.navigator.setNavigator({
        title: '导航栏',
        leftText: '返回',
        leftIcon: 'back.png',
        rightFirstIcon: 'icon_1.png',
        rightSecondIcon: 'icon_2.png',
        success: function(res) {
            console.log(res.result)
        },
        error: function(error) {
            console.log(error.msg)
        }
    })
```

#### Promise
```javascript
    syberh.navigator.setNavigator({
        title: '导航栏',
        leftText: '返回',
        leftIcon: 'back.png',
        rightFirstIcon: 'icon_1.png',
        rightSecondIcon: 'icon_2.png'
    }).then(function(res) {
        console.log(res.result)
    }).catch(function(error) {
        console.log(error.msg)
    })
```
