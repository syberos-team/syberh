/*
* This file is part of file-manager
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*       Xue Jun <zhanghuanlin@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

import QtQuick 2.0
import com.syberos.basewidgets 2.0
import org.nemomobile.thumbnailer 1.0
import "../js/util/tool.js" as Tool
import "SUI.js" as UI

CEditListViewDelegate {
    id: fileDelegt
    width: parent.width
    height: UI.FILE_LIST_HEIGHT

    property bool isNormalStatus: false //防止刚进入列表时，触发uncheckedAnimation的动画

    onClicked: {
        isNormalStatus = true;
    }

    Rectangle {
        id: listItem
        width: parent.width
        height: UI.FILE_LIST_HEIGHT - 1
        color: fileDelegt.pressed ? "#dddddd" : "#ffffff"
        Image {
            id: icon
            anchors.left: parent.left
            anchors.leftMargin: UI.DEFAULT_MARGIN_LEFT
            anchors.verticalCenter: parent.verticalCenter
            visible: !icon_vi.visible
            height: UI.FILE_ICON_HEIGHT
            width: UI.FILE_ICON_WIDTH
            source: fileUtils.getIcon(filePath, mimeType) //iconSrc
            asynchronous: true
            sourceSize: Qt.size(width, height) //nemoThumbnail need
            clip: true
        }

        Thumbnail {
            id: icon_vi
            width: UI.FILE_ICON_WIDTH
            height: UI.FILE_ICON_HEIGHT
            anchors.left: parent.left
            anchors.leftMargin: UI.DEFAULT_MARGIN_LEFT
            anchors.verticalCenter: parent.verticalCenter
            visible: (fileUtils.getFileType(filePath) === "image" || fileUtils.getFileType(filePath) === "video") ? true : false
            clip: true

            sourceSize.width: UI.FILE_ICON_WIDTH
            sourceSize.height: UI.FILE_ICON_HEIGHT
            source: "file://" + encodeURIComponent(filePath)
            mimeType : fileUtils.getFileType(filePath)
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: icon.visible ? icon.right : icon_vi.right
            anchors.leftMargin: UI.FILE_LIST_ROW_SPACING
            anchors.right: parent.right
            spacing: UI.FILE_LIST_COLUMN_SPACING
            clip: true

            Text {
                id: fileNameItem
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: UI.DEFAULT_MARGIN_RIGHT
                font.pixelSize: UI.FILE_NAME_SIZE
                text: filePath === fileUtils.innerStoragePath ? qsTr("手机") : (filePath == "/mnt/sdcard" ? qsTr("SD卡") : fileName) //typeModel.data(index, fileName) //model.fileName
                wrapMode: Text.NoWrap
                elide: Text.ElideMiddle
            }

            Row {
                spacing: UI.FILE_LIST_ROW_SPACING

                Text {
                    id: fileSizeItem
                    text: fileUtils.isFile(filePath) ? Tool.getSizeStr(fileSize) :
                                                       qsTr("%n 项", "", fileSize)
                    font.pixelSize: UI.FILE_INFO_SIZE
                    color: UI.FILE_INFO_COLOR
                }
                Text {
                    id: modifyDateItem
                    visible: !(filePath == fileUtils.innerStoragePath||filePath == "/mnt/sdcard")
                    text: Qt.formatDateTime(lastModified, "yyyy-M-d h:mm") //fileModifyDate
                    font.pixelSize: UI.FILE_INFO_SIZE
                    color: UI.FILE_INFO_COLOR
                }
            }
        } //end Column{ part3

    } //end listItem

    Image {
        id: bottomLine
        anchors.top: listItem.bottom
        width: parent.width
        source: "qrc:/img/line.png"
    }
} //end CEditListViewDelegate {
