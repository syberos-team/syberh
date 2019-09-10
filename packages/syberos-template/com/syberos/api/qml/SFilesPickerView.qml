/*
* This file is part of file-manager
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*       Zhenbin Cai <caizhenbin@syberos.com>
*       Xuan Liu <liuxuan@syberos.com>
*       Pengcheng Zhang <zhangpengcheng@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/
import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "SUI.js" as UI
import "Sfm.js" as FM

Rectangle {
    id: fileListRect
    width: parent.width
    height: parent.height
    focus: true

    property string titleText: "" // 页面标题
    property bool leftItemEnabled: false // 左侧区域是否展示
    property bool titleAreaEnable: fileListRect.titleText || fileListRect.leftItemEnabled // 标题区域区域是否展示


    Keys.onReleased: {
        if (event.key === Qt.Key_Back) {
            var curPath = typeModel.path;
            if (curPath !== "") {
                if (curPath === fileUtils.innerStoragePath || curPath === "/mnt/sdcard") {
                    typeModel.path = "";
                } else {
                    typeModel.path = FM.getDir(typeModel.path);
                }
            } else {
                toptitle.leftItemTriggered();
            }
            event.accepted = true;
        }
    }


    CTitleBar {
        id: toptitle
        visible: fileListRect.titleText || fileListRect.leftItemEnabled
        anchors.top: parent.top
        height: UI.TITLEBAR_HEIGHT
        titleText: fileListRect.titleText
        titleAreaCentered: true
        leftItemEnabled: fileListRect.leftItemEnabled

        titlePixelSize: gUiConst.getValue("S2")
        titleTextColor: gUiConst.getValue("CT1")
        leftItemText: ""
        leftItemPixelSize: gUiConst.getValue("S5")
        leftItemTextColor: gUiConst.getValue("CT1")

        onLeftItemTriggered: {
            var curPath = typeModel.path;
            if (curPath !== "") {
                if (curPath === fileUtils.innerStoragePath || curPath === "/mnt/sdcard") {
                    typeModel.path = "";
                } else {
                    typeModel.path = FM.getDir(typeModel.path);
                }
            } else {
                filesPicker.cancel();
                pageStack.pop();
            }
        }
    }

    CIconLabel {
        id: noItemArea
        visible: fileList.count === 0 ? true : false
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left
        z: fileList.z + 1
        iconSource: "qrc:/img/document.png"
        text: "暂无文件"
    } //end noItemArea

    CEditListView {
        id: fileList
        anchors.top: titleAreaEnable ? toptitle.bottom : parent.top
        anchors.bottom: parent.bottom
        width: parent.width
        clip: true
        interactive: true
        editable: false //Disable editing

        Rectangle {
            anchors.fill: parent
            color: "white"
            z: parent.z - 1
        }

        model: (category === 0) ? typeModel : galleryModel
        delegate: SDelegateComponent {
            id: fileDelegt
            width: fileList.width

            onClicked: {
                if (!isFile) { //dir
                    typeModel.path = filePath;
                } else if (!filesPicker.isDirMode){ //file(for select file not dir)
                    filesPicker.ok(filePath);
                    pageStack.pop();
                }
            } //end onClicked
        } //end DelegateComponent{

    } //end CEditListView {
}


