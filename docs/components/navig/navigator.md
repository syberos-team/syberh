---
title: navigator
---

导航栏组件，主要用于头部导航。

### 参数
| 参数名     | 类型    | 是否必填 | 描述                            |
| ---------- | ------- | -------- | ---------------------------- |
| title | String  | 否      | 标题文字      |
| leftText | String | 否       | 左边文字      |
| leftIcon | String | 否       | 左边图标      |
| rightFirstIcon | String | 否       | 从右到左，第一个图标      |
| rightSecondIcon | String | 否       | 从右到左，第二个图标      |
| callback | function(res) | 否       | 执行操作成功后的回调, res.result, 用户按下的类型 <br/> "0"是左边第一个图标类型点击事件 <br/>"1"是从右到左第一个图标类型点击事件<br/>"2"是从右到左第二个图标类型点击事件      |



### 代码示例
```javascript
    syber.navigator({
        title: '导航栏',
        leftText: '返回',
        leftIcon: 'back.png',
        rightFirstIcon: 'icon_1.png',
        rightSecondIcon: 'icon_2.png'
    }, function(res) {
        const result = res.result
        
        if (result === "0") {
            
        } else if (result === "1") {
            
        } else if (result === "2") {
            
        }
    })
```
