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
import "SUI.js" as UI
import "Sfm.js" as FM

Rectangle {
    id: fileListRect
    width: parent.width
    height: parent.height
    focus: true

    property int selectCnt: 0

    Keys.onReleased: {
        if (event.key === Qt.Key_Back) {
            console.debug("----- back key triggered, currentPath-----", typeModel.path);
            var curPath = typeModel.path;
            if (curPath !== "") {
                if (curPath === fileUtils.innerStoragePath || curPath === "/mnt/sdcard") {
                    typeModel.path = "";
                } else {
                    typeModel.path = FM.getDir(typeModel.path);
                }
            } else {
                console.log("Reach the top, now quit------------- ");
            }
            event.accepted = true;
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
        anchors.top: parent.top
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
                console.log(filePath + " is been clicked---------------");
                if (!isFile) { //dir
                    typeModel.path = filePath;
                } else if (!filesPicker.isDirMode){ //file(for select file not dir)
                    filesPicker.ok(filePath);
                    pageStack.pop();
                }
            } //end onClicked
        } //end DelegateComponent{

        Component.onCompleted: {
            console.log("fileList Component.onCompleted------", fileList.count);
        }
    } //end CEditListView {
}


