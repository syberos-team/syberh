/*
 * This file is part of syberos-toolkit-core
 * Copyright (C) 2015 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
 * Authors:
 *       zhao pan <zhaopan@syberos.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
 */

import QtQuick 2.3
import com.syberos.basewidgets 2.0
/*!
   \qmltype SAlert
   \inqmlmodule com.syberos.basewidgets
   \since 2.0
   \ingroup controls
   \brief 默认对话框控件

   SAlert主要由五个部分组成：背景区，对话框背景区，标题区，内容区，按钮区。
   其中浮层背景不可定制，其余部分可根据用户需求自行定制。

   示例代码:
   \qml
   SAlert {
       id: salert
       titleText: "message title"
       messageText: "message content"
   }
   \endqml
*/

sconfirm {
    id: salert
    titleText: 'xuejun'
    messageText: 'haha'
}
