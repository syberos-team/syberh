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
   \brief 默认弹出框控件

   示例代码:
   \qml
   SAlert {
       id: salert
       titleText: "message title"
       messageText: "message content"
   }
   \endqml
*/

SConfirm {
    id: salert
    titleText: ''
    messageText: ''
}
