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
//import "./default/CPhotoTranslate"

Loader{
    anchors.fill: parent
    sourceComponent: CIconLabel {
        text: CPhotoTranslate.noPhoto
        iconSource: "../images/default.png"
        color: gUiConst.getValue("CT1")
        pixelSize: env.dp(gUiConst.getValue("S3"))
        spacing: env.dp(50)
    }
}


