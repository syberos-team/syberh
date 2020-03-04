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
|常量 |	键值（16进制） |
| ---- |	:----: |
|Qt::Key_Escape	|	0x01000000	 |
|Qt::Key_Tab	|	0x01000001	 |
|Qt::Key_Backtab	|	0x01000002	 |
|Qt::Key_Backspace	|	0x01000003	 
|Qt::Key_Return	| 0x01000004	 |
|Qt::Key_Enter	| 0x01000005|
|Qt::Key_Insert	| 0x01000006	 |
|Qt::Key_Delete	| 0x01000007	 |
|Qt::Key_Pause	| 0x01000008|
|Qt::Key_Print	| 0x01000009	 |
|Qt::Key_SysReq	| 0x0100000a	 |
|Qt::Key_Clear	| 0x0100000b	 |
|Qt::Key_Home	| 0x01000010	| 
|Qt::Key_End	| 0x01000011	| 
|Qt::Key_Left	| 0x01000012	| 
|Qt::Key_Up	| 0x01000013	  |
|Qt::Key_Right	| 0x01000014	  |
|Qt::Key_Down	| 0x01000015	  |
|Qt::Key_PageUp	| 0x01000016	  |
|Qt::Key_PageDown	| 0x01000017	   |
|Qt::Key_Super_L	| 0x01000053	  |
|Qt::Key_Super_R	| 0x01000054	  |
|Qt::Key_Menu	    |0x01000055	  |
|Qt::Key_Hyper_L	| 0x01000056	  |
|Qt::Key_Hyper_R	| 0x01000057	  |
|Qt::Key_Help	    | 0x01000058	  |
|Qt::Key_Direction_L	|0x01000059	  |
|Qt::Key_Direction_R	| 0x01000060	  |
|Qt::Key_Space	      |0x20 |
|Qt::Key_0	| 0x30	|
|Qt::Key_1	| 0x31	|
|Qt::Key_2	| 0x32	|
|Qt::Key_3	| 0x33	|
|Qt::Key_4	| 0x34	|
|Qt::Key_5	| 0x35	|
|Qt::Key_6	| 0x36	|
|Qt::Key_7	| 0x37	|
|Qt::Key_8	| 0x38	|
|Qt::Key_9	| 0x39	|
|Qt::Key_Colon	| 0x3a	 |
|Qt::Key_Semicolon	| 0x3b	 |
|Qt::Key_Less	| 0x3c	 |
|Qt::Key_Equal	| 0x3d	 |
|Qt::Key_Greater	| 0x3e	 |
|Qt::Key_Question	| 0x3f	 |
|Qt::Key_At	| 0x40	 |
|Qt::Key_A	| 0x41	 |
|Qt::Key_B	| 0x42	 |
|Qt::Key_C	| 0x43	 |
|Qt::Key_D	| 0x44	 |
|Qt::Key_E	| 0x45	 |
|Qt::Key_F	| 0x46	 |
|Qt::Key_G	| 0x47	 |
|Qt::Key_H	| 0x48	 |
|Qt::Key_I	| 0x49	 |
|Qt::Key_J	| 0x4a	 |
|Qt::Key_K	| 0x4b	 |
|Qt::Key_L	| 0x4c	 |
|Qt::Key_M	| 0x4d	 |
|Qt::Key_N	| 0x4e	 |
|Qt::Key_O	| 0x4f	 |
|Qt::Key_P	| 0x50	 |
|Qt::Key_Q	| 0x51	 |
|Qt::Key_R	| 0x52	 |
|Qt::Key_S	| 0x53	 |
|Qt::Key_T	| 0x54	 |
|Qt::Key_U	| 0x55	 |
|Qt::Key_V	| 0x56	 |
|Qt::Key_W	| 0x57	 |
|Qt::Key_X	| 0x58	 |
|Qt::Key_Y	| 0x59	 |
|Qt::Key_Z	| 0x5a	 |
|Qt::Key_Back	| 0x01000061	 |
|Qt::Key_Forward	| 0x01000062	 |
|Qt::Key_Stop|	0x01000063	 |
|Qt::Key_Refresh	|	0x01000064	 |
|Qt::Key_VolumeDown	|	0x01000070	 |
|Qt::Key_VolumeMute	|	0x01000071	 |
|Qt::Key_VolumeUp	|	0x01000072	 |
|Qt::Key_HomePage	|	0x01000090|
|Qt::Key_PowerOff	|	0x010000b7	 |
|Qt::Key_WakeUp	|	0x010000b8	 |
|Qt::Key_BrightnessAdjust	|	0x010000c2	 |
|Qt::Key_Finance	|	0x010000c3	 |
|Qt::Key_Community	|	0x010000c4	 |
|Qt::Key_AudioRewind	|	0x010000c5	 |
|Qt::Key_BackForward	|	0x010000c6	 |
|Qt::Key_ClearGrab	|	0x010000cd	 |
|Qt::Key_Close	|	0x010000ce	 |
|Qt::Key_Copy	|	0x010000cf	 |
|Qt::Key_Cut	|	0x010000d0 |
|Qt::Key_SplitScreen	|	0x010000ed	 |
|Qt::Key_TaskPane	|	0x010000ef	 |
|Qt::Key_Terminal	|	0x010000f0	 |
|Qt::Key_Tools	|	0x010000f1	 |



