---
title: 订阅事件
---

订阅事件在任何页面都可以订阅

## onResize

屏幕旋转的订阅事件，在[全局配置](apis/app/setAppOrientation.html)或者[路由](apis/router/router.html)里面相关API会触发

#### object result 回调函数参数
#### 参数
| 属性     | 类型  | 描述                         |
| ---------- | ------- | ----------------------------------
| pageOrientation | number  | 当前页面的方向(0: 自动旋转，1：竖屏， 2：横屏， 8：横屏反向)  |
| appOrientation | number  | 当前应用的方向(0: 自动旋转，1：竖屏， 2：横屏， 8：横屏反向)  |


### 代码示例
``` javascript
syberh.subscribe('onResize', function (result) {
    console.log("收到屏幕旋转消息: ", JSON.stringify(result));
});
```

## onKeyRelease

设备物理按键的订阅事件。返回按键键值，和`Qt::Key`保持一致，下面列出了常用的键值对

#### object result 回调函数参数
#### 参数
| 属性     | 类型  | 描述                         |
| ---------- | ------- | ----------------------------------
| value | number  | 返回的按键键值  |


### 代码示例
``` javascript
syberh.subscribe('onKeyRelease', function (res) {
    console.log("onKeyRelease: ", res.value);
});
```

#### 常见的按键键值对 
|常量 |	键值（16进制） | 键值（10进制） | 对应的按键 |
| ---- |	:----: |	:----: |	:----: |
|Qt::Key_VolumeUp	           |	0x01000072	 | 16777330 | 音量+键 |
|Qt::Key_VolumeDown	         |	0x01000070	 | 16777328 | 音量-键 |
|Qt::Key_PowerOff	           |	0x010000b7	 | 16777399 | 电源键 |
|Qt::Key_Back	               | 0x01000061	   | 16777313 | 返回键 |
|Qt::Key_Left	               | 0x01000012	   |           | ←     |
|Qt::Key_Up	                 | 0x01000013	   |           | ↑     |
|Qt::Key_Right	             | 0x01000014	   |           | →     |
|Qt::Key_Down	               | 0x01000015	   |           | ↓     |
|Qt::Key_Space	             |   0x20        |           | 空格键 |
|Qt::Key_Minus               |  0x2d         |           |   -键  |
|Qt::Key_Delete              |  0x01000007   |           |  Delete键  |
|Qt::Key_Call	               | 0x01100004    |           |  A key to answer or initiate a call (see Qt::Key_ToggleCallHangup for a key to toggle current call state)  |
|Qt::Key_ToggleCallHangup	   | 0x01100007    |           | A key to toggle the current call state (ie. either answer, or hangup) depending on current call state        | 
|Qt::Key_Hangup	             | 0x01100005	   |           |A key to end an ongoing call (see Qt::Key_ToggleCallHangup for a key to toggle current call state) |
|Qt::Key_0	                 | 0x30	         |           | 数字0键 |
|Qt::Key_1	                 | 0x31	         |           | 数字1键 |
|Qt::Key_2	                 | 0x32	         |           | 数字2键 |
|Qt::Key_3	                 | 0x33	         |           | 数字3键 |
|Qt::Key_4	                 | 0x34	         |           | 数字4键 |
|Qt::Key_5	                 | 0x35	         |           | 数字5键 |
|Qt::Key_6	                 | 0x36	         |           | 数字6键 |
|Qt::Key_7	                 | 0x37	         |           | 数字7键 |
|Qt::Key_8	                 | 0x38	         |           | 数字8键 |
|Qt::Key_9	                 | 0x39	         |           | 数字9键 |
|Qt::Key_F1	                 | 0x01000030	   |           | F1     |
|Qt::Key_F2	                 | 0x01000031	   |           | F2     |
|Qt::Key_F3	                 | 0x01000032	   |           | F3     |
|Qt::Key_F4	                 | 0x01000033	   |           | F4     |
|Qt::Key_A	                 | 0x41          |           | 字母键 |
|Qt::Key_B	                 | 0x42          |           |        |
|Qt::Key_C	                 | 0x43          |           |        |
|Qt::Key_D	                 | 0x44          |           |        |
|Qt::Key_E	                 | 0x45          |           |        |
|Qt::Key_F	                 | 0x46          |           |        |
|Qt::Key_G	                 | 0x47          |           |        |
|Qt::Key_H	                 | 0x48          |           |        |
|Qt::Key_I	                 | 0x49          |           |        |
|Qt::Key_J	                 | 0x4a          |           |        |
|Qt::Key_K	                 | 0x4b          |           |        |
|Qt::Key_L	                 | 0x4c          |           |        |
|Qt::Key_M	                 | 0x4d          |           |        |
|Qt::Key_N	                 | 0x4e          |           |        |
|Qt::Key_O	                 | 0x4f          |           |        |
|Qt::Key_P	                 | 0x50          |           |        |
|Qt::Key_Q	                 | 0x51          |           |        |
|Qt::Key_R	                 | 0x52          |           |        |
|Qt::Key_S	                 | 0x53          |           |        |
|Qt::Key_T	                 | 0x54          |           |        |
|Qt::Key_U	                 | 0x55          |           |        |
|Qt::Key_V	                 | 0x56          |           |        |
|Qt::Key_W	                 | 0x57          |           |        |
|Qt::Key_X	                 | 0x58          |           |        |
|Qt::Key_Y	                 | 0x59          |           |        |
|Qt::Key_Z	                 | 0x5a          |           |        |
