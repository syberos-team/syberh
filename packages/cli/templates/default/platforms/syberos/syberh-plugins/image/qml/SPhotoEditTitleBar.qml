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
/*
    图片应用主窗口的TitleBar
*/
CEditTitleBar{
    id: sPhotoEdittitleBar
    width: parent.width

    leftItemEnabled: false
    rightItemEnabled: false

    titleText: PhotoTranslate.all_photos
    titleTextColor: gUiConst.getValue("CTB1")
    titlePixelSize: editView ? ( editView.editing ? env.dp(gUiConst.getValue("S6")) : env.dp(gUiConst.getValue("S3")) ) : env.dp(gUiConst.getValue("S3"))

    editLeftItemTextColor: gUiConst.getValue("CTB1")
    editLeftItemPixelSize: env.dp(gUiConst.getValue("S3"))
    editLeftItemBackgroundEnabled: false
    editLeftItemSize: Qt.size(env.dp(80),env.dp(56))
    editRightItemRightMargin: 0
    editLeftItemLeftMargin: env.dp(20)

    editRightComponent: null
    editLeftComponent: CButton{
        text:editLeftItemText
        textColor:editLeftItemTextColor
        pixelSize: editLeftItemPixelSize
        backgroundEnabled: editLeftItemBackgroundEnabled
        onClicked: {
            sPhotoEdittitleBar.canceled()
        }
    }

    /*!标题居中显示 */
    titleAreaCentered: true

    Component.onCompleted: {
        if(backgroundEnabled){
            backgroundItem.color = "#F4000000"
        }
    }
}
