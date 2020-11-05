/***************************************************************************
 *
 * Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
 *
 * Authors:
 *       Liu Jingpeng <liujingpeng@syberos.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
 ****************************************************************************/

import QtQuick 2.5
import com.syberos.basewidgets 2.0


CInputDialog {
    id: promptDialog

    property alias text: promptDialog.titleText

    canceledOnBackKeyReleased: false
    canceledOnOutareaClicked: false

    acceptedButtonText: "确定"
    rejectButtonText: "取消"
}
