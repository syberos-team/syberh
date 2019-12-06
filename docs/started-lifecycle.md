---
title: 生命周期
---

页面的生命周期

![生命周期图示](/img/life.jpg)

## 事件
| 属性      |　描述　| 
| ---      | ------ |
| onReady  | 监听页面初次渲染完成 
| onShow   | 监听页面显示 
| onHide   | 监听页面隐藏 
| onUnload | 监听页面卸载 

## onReady

页面初次渲染完成时触发。一个页面只会调用一次，代表页面已经准备妥当，可以和视图层进行交互。

## onShow

关掉当前页，返回上一个页面时触发。如当前页`navigateBack`。

## onHide

页面隐藏时触发。 如`navigateTo`。

## onUnload

页面卸载时触发。如`redirectTo`或`reLaunch`或`navigateBack`到其他页面时。

## 代码示例
``` javascript
syberh.subscribe('onReady', function () {
  console.log('page onReady')
});

syberh.subscribe('onShow', function () {
  console.log('page onShow')
});

syberh.subscribe('onHide', function () {
  console.log('page onHide')
});

syberh.subscribe('onUnload', function () {
  console.log('page onUnload')
});
```

