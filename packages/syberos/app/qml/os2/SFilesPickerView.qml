/*
* This file is part of syberh
*
* Copyright (C) 2019 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*       Xue Jun <xuejun@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/
import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../js/util/tool.js" as Tool

Rectangle {
    id: fileListRect
    width: parent.width
    height: parent.height
    focus: true

    // 页面标题
    property string titleText: ""

    // 左侧区域是否展示
    property bool leftItemEnabled: false

    // 标题区域区域是否展示
    property bool titleAreaEnable: fileListRect.titleText || fileListRect.leftItemEnabled

    // 选中个数
    property int selectCnt: 0

    Keys.onReleased: {
        if (event.key === Qt.Key_Back) {
            var curPath = typeModel.path;
            if (curPath !== "") {
                if (curPath === fileUtils.innerStoragePath || curPath === "/mnt/sdcard") {
                    typeModel.path = "";
                } else {
                    typeModel.path = Tool.getDir(typeModel.path);
                }
            } else {
                toptitle.leftItemTriggered();
            }
            event.accepted = true;
        }
    }

    onSelectCntChanged: {
        if (fileListRect.selectCnt > 0) {
            toptitle.rightItem.enabled = true;
        } else {
            toptitle.rightItem.enabled = false;
        }
    }

    Connections {
        target: typeModel
        onPathChanged: {
            if (!filesPicker.isDirMode) {
                fileListRect.selectCnt = 0; //trigger onSelectCntChanged signal
            } else {
                if (typeModel.path === "") {
                    toptitle.rightItem.enabled = false;
                } else {
                    if(fileUtils.checkWritePermission(typeModel.path)){
                         toptitle.rightItem.enabled = true;
                    } else {
                        gToast.requestToast((os.i18n.ctr(qsTr("the path don't have write permission,please choose agagin!"))))
                         toptitle.rightItem.enabled = false;
                    }
                }
            }
        }
    }

    CTitleBar {
        id: toptitle
        visible: fileListRect.titleText || fileListRect.leftItemEnabled
        anchors.top: parent.top
        height: Tool.UI.TITLEBAR_HEIGHT
        titleText: fileListRect.titleText
        titleAreaCentered: true
        leftItemEnabled: fileListRect.leftItemEnabled

        titlePixelSize: env.dp(gUiConst.getValue("S2"))
        titleTextColor: gUiConst.getValue("CT1")
        leftItemText: ""
        leftItemPixelSize: env.dp(gUiConst.getValue("S5"))
        leftItemTextColor: gUiConst.getValue("CT1")
        rightItemEnabled: true
        rightItemText: "确定"

        onLeftItemTriggered: {
            var curPath = typeModel.path;
            if (curPath !== "") {
                if (curPath === fileUtils.innerStoragePath || curPath === "/mnt/sdcard") {
                    typeModel.path = "";
                } else {
                    typeModel.path = Tool.getDir(typeModel.path);
                }
            } else {
                filesPicker.cancel();
//                在SWebview.qml中引用了该页面，所以退出页面的信号得在接受信号的地方处理是否退出页面
//                pageStack.pop();
            }
        }

        onRightItemTriggered: {
            // 文件
            if (!filesPicker.isDirMode) { //for email
                if (filesPicker.category === 0) { //select file for all type
                    filesPicker.filesPath = typeModel.getSelectedFilesPath();
                } else if (filesPicker.category > 0) {
                    filesPicker.filesPath = galleryModel.getSelectedFilesPath();
                }

                console.log("Title Bar right Item is been clicked, filesPath-----", filesPicker.filesPath);
                var files = []
                for (var i in filesPicker.filesPath) {
                    var filePath = filesPicker.filesPath[i]
                    var size = fileutil.getInfoSize(filePath)
                    // 自己截取的名字
                    var name = filePath.split('/').reverse()[0]
                    files.push({
                        path: "file://" + filePath,
                        size: size,
                        name: name,
                    })
                }
                filesPicker.ok(files);
//                在SWebview.qml中引用了该页面，所以退出页面的信号得在接受信号的地方处理是否退出页面
//                pageStack.pop();
            } else {
                // 文件夹
                filesPicker.dirPath = filesPicker.getDirPath();
            }
        }

        Component.onCompleted: {
            toptitle.rightItem.enabled = false;
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

                    // 超过选中的最大值，如果是取消选中，可以继续操作
                    if (fileListRect.selectCnt >= filesPicker.count) {
                        console.log('超过选中的最大值')
                        // 之前是选中状态，本次操作取消选中
                        if (isSelected) {
                            isNormalStatus = true
                        } else {
                            // 选中数量到了最大值，还要选新的数据，直接返回
                            isNormalStatus = false
                            return
                        }
                    }

                    // 正常操作选中不选中
                    isNormalStatus = true
                    isSelected = !isSelected

                    if (isSelected) {
                        fileListRect.selectCnt++;
                    } else {
                        fileListRect.selectCnt--;
                    }

                }
            } //end onClicked
        } //end DelegateComponent{

    } //end CEditListView {
}


