/*
* This file is part of syberh
*
* Copyright (C) 2019 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
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

CEditListViewDelegate {
    id: fileDelegt
    width: parent.width
    height: Tool.UI.FILE_LIST_HEIGHT

    property bool isNormalStatus: false //防止刚进入列表时，触发uncheckedAnimation的动画

    Rectangle {
        id: listItem
        width: parent.width
        height: Tool.UI.FILE_LIST_HEIGHT - 1
        color: fileDelegt.pressed ? "#dddddd" : "#ffffff"
        Image {
            id: icon
            anchors.left: parent.left
            anchors.leftMargin: Tool.UI.DEFAULT_MARGIN_LEFT
            anchors.verticalCenter: parent.verticalCenter
            visible: !icon_vi.visible
            height: Tool.UI.FILE_ICON_HEIGHT
            width: Tool.UI.FILE_ICON_WIDTH
            source: fileUtils.getIcon(filePath, mimeType) //iconSrc
            asynchronous: true
            sourceSize: Qt.size(width, height) //nemoThumbnail need
            clip: true
        }

        Thumbnail {
            id: icon_vi
            width: Tool.UI.FILE_ICON_WIDTH
            height: Tool.UI.FILE_ICON_HEIGHT
            anchors.left: parent.left
            anchors.leftMargin: Tool.UI.DEFAULT_MARGIN_LEFT
            anchors.verticalCenter: parent.verticalCenter
            visible: (fileUtils.getFileType(filePath) === "image" || fileUtils.getFileType(filePath) === "video") ? true : false
            clip: true

            sourceSize.width: Tool.UI.FILE_ICON_WIDTH
            sourceSize.height: Tool.UI.FILE_ICON_HEIGHT
            source: "file://" + encodeURIComponent(filePath)
            mimeType : fileUtils.getFileType(filePath)
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: icon.visible ? icon.right : icon_vi.right
            anchors.leftMargin: Tool.UI.FILE_LIST_ROW_SPACING
            anchors.right: parent.right
            spacing: Tool.UI.FILE_LIST_COLUMN_SPACING
            clip: true

            Text {
                id: fileNameItem
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: Tool.UI.DEFAULT_MARGIN_RIGHT + selectIcon.anchors.rightMargin + selectIcon.width
                font.pixelSize: Tool.UI.FILE_NAME_SIZE
                text: filePath === fileUtils?fileUtils.innerStoragePath: "" ? qsTr("手机") : (filePath == "/mnt/sdcard" ? qsTr("SD卡") : (fileName === 'user' ? qsTr("手机") : fileName)) //typeModel.data(index, fileName) //model.fileName
                wrapMode: Text.NoWrap
                elide: Text.ElideRight
            }

            Row {
                spacing: Tool.UI.FILE_LIST_ROW_SPACING

                Text {
                    id: fileSizeItem
                    text: fileUtils.isFile(filePath) ? Tool.getSizeStr(fileSize) :
                                                       qsTr("%n 项", "", fileSize)
                    font.pixelSize: Tool.UI.FILE_INFO_SIZE
                    color: Tool.UI.FILE_INFO_COLOR
                }
                Text {
                    id: modifyDateItem
                    visible: !(filePath === fileUtils?fileUtils.innerStoragePath:""||filePath == "/mnt/sdcard")
                    text: Qt.formatDateTime(lastModified, "yyyy-M-d h:mm") //fileModifyDate
                    font.pixelSize: Tool.UI.FILE_INFO_SIZE
                    color: Tool.UI.FILE_INFO_COLOR
                }
            }
        } //end Column{ part3

        Item{
            id: selectIcon
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: iconRightMargin
            implicitWidth: 40
            implicitHeight: 40
            visible: (!filesPicker.isDirMode && isFile) ? true : false

            /*! 标记图标选中颜色。*/
            property color checkedColor: "#ff2828"
            property QtObject editView: fileDelegt.ListView.view
            /*! 标记图标距离Item右边的距离，默认值20。*/
            property int iconRightMargin: 40
            /*! 标记图标非选中颜色。*/
            property color normalColor: "#999999"
            property int duration: editView.moving ? 0 : 200

            Rectangle {
                id: defaultRect
                width: parent.width
                height: width
                radius: width/2
                color: "transparent"
                border{ color: selectIcon.normalColor; width: 3 }

                Rectangle{
                    id: centerRect
                    width: parent.width
                    height: width
                    radius: width/2
                    color: selectIcon.checkedColor
                    anchors.centerIn: parent
                    scale: 0.0
                }

                SequentialAnimation {
                    id: checkedAnimation
                    running: isSelected
                    NumberAnimation { target: centerRect; property: "scale"; to: 1.0; duration: selectIcon.duration }
                    ScriptAction{ script: {defaultRect.border.color = selectIcon.checkedColor; } }
                    NumberAnimation { target: centerRect; property: "scale"; to: 0.35; duration: selectIcon.duration }
                    NumberAnimation { target: centerRect; property: "scale"; to: 0.65; duration: selectIcon.duration/2.0 }
                    NumberAnimation { target: centerRect; property: "scale"; to: 0.5; duration: selectIcon.duration/2.0 }
                }

                SequentialAnimation {
                    id: uncheckedAnimation
                    running: isNormalStatus && !isSelected
                    NumberAnimation { target: centerRect; property: "scale"; to: 1.0; duration: selectIcon.duration }
                    ScriptAction{ script: {defaultRect.border.color = selectIcon.normalColor; } }
                    NumberAnimation { target: centerRect; property: "scale"; to: 0.0; duration: selectIcon.duration }
                }
            }
        }

    } //end listItem

    Image {
        id: bottomLine
        anchors.top: listItem.bottom
        width: parent.width
        source: "qrc:/img/line.png"
    }
} //end CEditListViewDelegate {
