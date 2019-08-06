---
title: navigator
---

导航栏组件，主要用于头部导航。

## 一般用法
```javascript
    syber.navigator({
        title: '导航栏',
        leftText: '返回',
        leftIcon: 'back.png',
        rightFirstIcon: 'icon_1.png',
        rightSecondIcon: 'icon_2.png'
    }, function(data) {
        const result = data.result
        
        if (result === "0") {
            
        } else if (result === "1") {
            
        } else if (result === "2") {
            
        }
    })
```

## 参数
| 参数 | 说明 | 类型 | 默认植 |
| --  | -- | -- | -- |
| title | 标题文字 | String | -
| leftText | 左边文字 | String | -
| leftIcon | 左边图标 | String | -
| rightFirstIcon | 从右到左，第一个图标 | String | -
| rightSecondIcon | 从右到左，第二个图标 | String | -

## 回调
- @callback, function，用户操作完成后的回调，参数是按下按钮上的文字信息
    + <code><font color='#e96900'>result</font></code>, string, 用户按下的类型,  "0"是左边第一个图标类型点击事件, "1"是从右到左第一个图标类型点击事件, "2"是从右到左第二个图标类型点击事件

