/*
* This file is part of syberh
*
* Copyright (C) 2019 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*       Liu jingpeng <liujingpeng@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/
import QtQuick 2.0
import com.syberos.basewidgets 2.0
import textEditor 1.0
import "../js/util.js" as Util

CPage {
    id: rootTextViewer
    statusBarHoldEnabled: true
    statusBarHoldItemColor: "white"
    orientationLock: CPageOrientation.LockPortrait

    property int page: -1
    property string filePath: ""

    onFilePathChanged: {
        textEditor.path = filePath
    }

    onPageChanged: {
        editor.text = textEditor.getContent(page);
    }

    TextEditor {
        id: textEditor
        path: filePath
        onPathChanged: {
            page = 0
        }
    }

    contentAreaItem: Item {
        CTitleBar {
            id: titleBar
            height: env.dp(106)
            leftItemEnabled: true
            rightItemEnabled: false
            titleAreaCentered: true

            titleText: Util.getFileNameNoSuffix(filePath)
            titlePixelSize: env.dp(gUiConst.getValue("S2"))
            titleTextColor: gUiConst.getValue("CT1")
            leftItemText: ""
            leftItemPixelSize: env.dp(gUiConst.getValue("S5"))
            leftItemTextColor: gUiConst.getValue("CT1")

            onLeftItemTriggered: pageStack.pop()
        }

        Rectangle {
            id: titleBarLine
            width: titleBar.width
            height: 1
            color: "#b3b3b3"
            anchors.top: titleBar.bottom

        }

        Rectangle {
            anchors.fill: parent
            color: "white"
            z: parent.z - 1
        }

        CTextArea {
            id: editor
            anchors.top: titleBarLine.bottom
            anchors.left: parent.left
            anchors.leftMargin: env.dp(4)
            anchors.right: parent.right
            anchors.rightMargin: env.dp(4)
            anchors.bottom: navBar.top
            anchors.bottomMargin: env.dp(8)
            readOnly: true

            font.pixelSize: env.dp(gUiConst.getValue("S4"))
            textColor: gUiConst.getValue("color05")
        }

        Image {
            width: navBar.width
            anchors.bottom: navBar.top
            source: "qrc:/img/editBarTopLine.png"
        }

        Rectangle {
            id: navBar
            width: parent.width
            height: textEditor.pageCount > 1 ? previousBtn.height + env.dp(24) : 0
            anchors.bottom: parent.bottom
            clip: true

            CButton {
                id: previousBtn
                pixelSize: env.dp(gUiConst.getValue("S4"))
                anchors.left: parent.left
                anchors.leftMargin: env.dp(16)
                anchors.verticalCenter: parent.verticalCenter
                enabled: page > 0
                text: "向前"
                onClicked: {
                    page--
                    editor.children[0].contentY = 0
                }
            }

            Text {
                anchors.centerIn: parent
                font.pixelSize: env.dp(gUiConst.getValue("S4"))
                text: (page + 1) // + " / " + textEditor.pageCount
            }

            CButton {
                id: nextBtn
                pixelSize: env.dp(gUiConst.getValue("S4"))
                anchors.right: parent.right
                anchors.rightMargin: env.dp(16)
                anchors.verticalCenter: parent.verticalCenter
                enabled: page < (textEditor.pageCount - 1)
                text: "向后"
                onClicked: {
                    page++
                    editor.children[0].contentY = 0
                }
            }
        }
    } //end contentAreaItem
}
