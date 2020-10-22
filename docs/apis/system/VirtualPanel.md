---
title: VirtualPanel
---

## syberh.system.setVirtualPanel(Object object)

设置系统虚拟按键显示隐藏

<!-- 支持`Promise` 使用。 -->

### 参数


#### Object object

| 属性    | 类型     | 必填 | 描述                                                         |
| ------- | -------- | -------- | ------------------------------------------------------------ |
| visible | boolean  | 是      | 设置虚拟按键显示状态      |
| success | function | 否       | 成功回调                                       |
| fail    | function | 否       | 失败回调                                       |

#### object.success 回调函数参数
#### 参数
| 属性           | 类型    | 描述                                 |
| -------------- | ------  | ------------------------------------ |
| visible       | boolean  | 当前系统虚拟按键显示状态     |

#### object.fail回调函数参数
#### 参数
| 属性 | 类型   | 描述     |
| ---- | ------ | -------- |
| code | String | 错误码   |
| msg  | String | 错误信息 |


### 代码示例
```js
syberh.system.setVirtualPanel({
	success:function(result){
        console.log('visible: ', result.visible);
    }
    fail:function(error){
        console.log('fail: ', error.code, error.msg);
    }
});
```
