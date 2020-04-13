import QtQuick 2.0
import QtQuick.Window 2.2
import com.syberos.basewidgets 2.0

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
    property string navigationBarTitle: ""

    // 标题文字居中居左
//    property string navigationBarTitlePosition: "center"

    // 导航栏背景色
    property string navigationBarBackgroundColor: ""

    // 导航栏字体颜色
    property string navigationBarColor: ""

    // 返回按钮是否展示
    property bool navigationBarBackIconEnable: true

    // 关闭按钮是否展示
    property bool navigationBarCloseIconEnable: true

    // 是否需要关闭当前webview且history.length>1 (从SWebview中canGoBack返回)
    property bool closeCurWebviewEnable: false

    // 设置成功的信号
    signal accepted()

    // 返回信号
    signal goBack()

    // 关闭当前webview信号
    signal closeCurWebview()

    // 显示导航栏
    function show(options){
        console.log("navigationBar show",title);
        navigationBar.visible = true;
        setNavigationBar(options)
    }

    // 设置标题
    function setTitle(title) {
        console.log('navigationBar title', title)
        navigationBarTitle = qsTr(title)
    }

    // 设置导航栏背景色
    function setBackgroundColor(color) {
        console.log('navigationBar color', color)
        navigationBarBackgroundColor = qsTr(color)
    }

    // 设置导航栏背景色
    function setColor(color) {
        console.log('navigationBar color', color)
        navigationBarColor = qsTr(color)
    }

    // 设置导航栏参数
    function setNavigationBar(options) {
        console.log('options', JSON.stringify(options))
        sNavigationBar.navigationBarTitle = options.navigationBarTitle
        sNavigationBar.navigationBarColor = options.navigationBarColor
        sNavigationBar.navigationBarBackgroundColor = options.navigationBarBackgroundColor
        sNavigationBar.navigationBarCloseIconEnable = options.navigationBarCloseIconEnable
        sNavigationBar.navigationBarBackIconEnable = options.navigationBarBackIconEnable
//        sNavigationBar.navigationBarTitlePosition = options.navigationBarTitlePosition
        console.log('navigationBarTitle--', navigationBarTitle)
        console.log('navigationBarBackgroundColor--', navigationBarBackgroundColor)
        console.log('navigationBarColor--', navigationBarColor)
        console.log('navigationBarHeight--', navigationBarHeight)
    }

    height: navigationBarHeight
    width: parent.width

    Rectangle {
        id: controlsRow
        height: navigationBarHeight
        width: parent.width
        color: navigationBarBackgroundColor

        // 导航栏下面的分界线
        Rectangle {
            id: line
            width: parent.width
            height: 1
            anchors.top: parent.top
            anchors.topMargin: navigationBarHeight - line.height
            color: '#B5B5B5'
            z: 999
        }

        Rectangle {
            id: backButton
            visible: navigationBarBackIconEnable
            color: navigationBarBackgroundColor
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
                onPressed: { parent.opacity = 0.9 }
                // 鼠标谈起恢复
                onReleased: { parent.opacity = 1 }
                onClicked: {               
                    console.log("MiniBrowser: Going backward in session history.")
                    // 发信号给SWebview
                    goBack()
                }
            }
        }

        Rectangle {
            id: closeButton
            visible: navigationBarCloseIconEnable && closeCurWebviewEnable
            color: navigationBarBackgroundColor
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
                // 鼠标按下变颜色
                onPressed: { if (parent.enabled) parent.opacity = 0.9 }
                // 鼠标谈起恢复
                onReleased: { parent.opacity = 1 }
                onClicked: {
                    console.log("MiniBrowser: closeCurWebview.")
                    closeCurWebview()
                }
            }
        }

        // 标题
        Text {
            id:navigationBarText
            font.pixelSize: titleFontSize
            color: navigationBarColor
            text: navigationBarTitle
            anchors.centerIn: parent

//            anchors.verticalCenter: parent.verticalCenter
//            anchors.verticalCenterOffset: 0
//            anchors.horizontalCenter: navigationBarTitlePosition === "left" ? undefined : parent.horizontalCenter
//            anchors.left: navigationBarTitlePosition === "left" ? (closeButton.visible ? closeButton.right : (backButton.visible ? backButton.right : parent.left)) : undefined
//            anchors.leftMargin: 10

        }
    }

}
