import QtQuick 2.0
import QtQuick.Window 2.2

import "../js/util/log.js" as LOG

Rectangle {
    id: navigationBar
    // 默认隐藏
    visible: false

    /*! 模态框和页面的缩放比例 */
    property real scaleFactor: Screen.width / 1080

    // 导航栏高度
    property real navigationBarHeight: 148 * scaleFactor

    // 导航栏左右两侧宽度
    property real navigationBarBothSidesWidth: 48 * scaleFactor

    // icon的宽高
    property real iconHeight: 52 * scaleFactor

    // 左侧icon的左右间距
    property real leftIconMargin: 20 * scaleFactor

    // 右侧icon的左右间距
    property real rightIconMargin: 30 * scaleFactor

    // 标题文字大写
    property real titleFontSize: 52 * scaleFactor

    // 标题文字
    property string titleText: ""

    // 左侧返回icon是否展示
    property bool leftIconShow: true

    // 是否需要关闭当前webview且history.length>1 (从SWebview中canGoBack返回)
    property bool closeCurWebviewEnable: false

    // 设置成功的信号
    signal accepted()

    // 返回信号
    signal goBack()

    // 关闭当前webview信号
    signal closeCurWebview()

    // 显示导航栏
    function show(title){
        console.log("navigationBar show",title);
        navigationBar.visible = true;
        if(title){
          setTitle(title);
        }
    }

    // 设置标题
    function setTitle(title) {
        console.log('navigationBar title',title,typeof title)
        titleText = qsTr(title)
    }

    height: navigationBarHeight
    width: parent.width

    Rectangle {
        id: controlsRow
        height: navigationBarHeight
        width: parent.width

        Rectangle {
            id: backButton
            visible: leftIconShow
            height: parent.height
            // 给元素扩大位置, 方便点击
            width: iconHeight + leftIconMargin * 2
            anchors.left: parent.left
            // 给元素扩大位置, 方便点击
            anchors.leftMargin: navigationBarBothSidesWidth - leftIconMargin

            Image {
                width: iconHeight
                height: iconHeight
                anchors.centerIn: parent
                source: "qrc:/com/syberos/api/res/navBack.png"
            }

            MouseArea {
                anchors.fill: parent
                // 鼠标按下变颜色
                onPressed: { parent.color = "#cfcfcf" }
                // 鼠标谈起恢复
                onReleased: { parent.color = "#efefef" }
                onClicked: {               
                    console.log("MiniBrowser: Going backward in session history.")
                    // 发信号给SWebview
                    goBack()
                }
            }
        }

        Rectangle {
            id: closeButton
            visible: closeCurWebviewEnable
            height: parent.height
            // 给元素扩大位置, 方便点击
            width: iconHeight + leftIconMargin * 2
            anchors.left: backButton.right
            // 给元素扩大位置, 方便点击
            anchors.leftMargin: leftIconMargin

            Image {
                width: iconHeight
                height: iconHeight
                anchors.centerIn: parent
                source: "qrc:/com/syberos/api/res/navClose.png"
            }

            MouseArea {
                anchors.fill: parent
                onPressed: { if (parent.enabled) parent.color = "#cfcfcf" }
                onReleased: { parent.color = "#efefef" }
                onClicked: {
                    console.log("MiniBrowser: closeCurWebview.")
                    closeCurWebview()
                }
            }
        }

        // 标题
        Text {
            id:navigationBarText
            anchors.centerIn: parent
            font.pixelSize: titleFontSize
            text: titleText
        }


    }



}
