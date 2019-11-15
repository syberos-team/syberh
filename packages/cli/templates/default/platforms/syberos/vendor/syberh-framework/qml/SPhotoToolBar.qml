/*
 * This file is part of Photos
 * Copyright (C) 2016 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
 * Authors:
 *       Dongshuang Zhao <zhaodongshuang@syberos.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
 */
import QtQuick 2.3
import com.syberos.basewidgets 2.0
/*
    窗口通用的ToolBar
*/
CFlowToolBar{
    width: parent.width
    anchors.bottom: parent.bottom
    backgroundEnabled: false
    propagateMouseEvents: false
    buttonColor: "#F4000000"
    textFontSize: env.dp(gUiConst.getValue("S4"))
    textColor: gUiConst.getValue("CTB1")
}
