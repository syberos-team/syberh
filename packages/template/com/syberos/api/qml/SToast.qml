/*
* This file is part of hybrid-core
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd.
All rights reserved.
*
* Authors:guohongfei
*
* guohongfei <guohongfei@syberos.com>
*
* This software, including documentation, is protected by
copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are
reserved.
*/

import QtQuick 2.3
import QtQuick.Window 2.2
import com.syberos.basewidgets 2.0
import "../js/util/tool.js" as Tool


Rectangle {
    id: stoast;

    /*! 模态框和页面的缩放比例 */
    property real scaleFactor: Screen.width / 1080

    /*! 提示的内容 */
    //property string title: ""
    /*! 提示的延迟时间 */
    readonly property real duration: 1500
    /*! 图标 */
    //property string icon: "success"
    /*! 图标路径 */
    //property string iconPath: ""
    /*! 一行文本的字符数（英文） */
    readonly property real textLength: 14

    /*! 成功信号，动画执行完发射 */
    signal accepted()

    width: unit.dp(330)
    height: scaleFactor * 330
    x: Screen.width/ 2 - width / 2
    y: Screen.height  / 2 - height / 2 - gScreenInfo.statusBarHeight

    color: "#000000"
    radius: 6
    opacity: 0

    Column {
        spacing: scaleFactor * 20;
        anchors.centerIn: parent
        Image {
            id: toastIcon
            anchors.horizontalCenter: parent.horizontalCenter
            width: scaleFactor * 141
            height: scaleFactor * 141
            source: ""
        }

        Text {
            id: toastText
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: scaleFactor * 40
            text: ""
            color: "white"
        }
    }

    NumberAnimation on opacity {
        id: showAnimation
        duration: 300
        from: 0
        to: 0.8
        running:false
    }

    NumberAnimation on opacity {
        id: hideAnimation
        duration: 500
        from: 0.8
        to: 0
        running:false
    }

    Timer{
        id: closeTimer
        interval: stoast.duration + showAnimation.duration
        repeat: false
        triggeredOnStart: false

        onTriggered: {
            closeTimer.stop();
            if(!hideAnimation.running){
                hideAnimation.start();

            }
        }
    }



    /*! 显示弹层。 */
    function show(title, icon, duration) {

        hide();

        if(!title){
            return "提示的内容不能为空";
        }

        if(!icon){
            icon = "success";
        }

        var strlength = Tool.getStrLength(title);
        if(icon !== "none" && strlength > 14){
            return "有图标时最多7个汉字长度的文本";
        }

        if(icon === "none" && strlength > 28 ){
            return "无图标时最多显示两行文本（14个汉字长度）";
        }

        if(duration){
            if (!(/(^[1-9]\d*$)/.test(duration))) {
                return "duration只能是正整数";
            }
            closeTimer.interval = parseInt(duration) + parseInt(showAnimation.duration);
        }

        accepted();

        stoast.width = stoast.scaleFactor * 330
        stoast.height = stoast.scaleFactor * 330
        toastIcon.visible = true;

        if(icon === "success"){
            toastIcon.source = "qrc:/com/syberos/api/res/toast-success.png";
            toastText.text = title;
        }else if(icon === "error"){
            toastIcon.source = "qrc:/com/syberos/api/res/toast-fail.png";
            toastText.text = title;
        }else if(icon === "none"){
            toastIcon.visible = false;
            toastText.text = Tool.getOutputStr(title, stoast.textLength);
            stoast.width = stoast.scaleFactor * toastText.contentWidth + 80
            stoast.height = stoast.scaleFactor * toastText.contentHeight + 80
        }

        if(!showAnimation.running){
            showAnimation.start();
        }
        closeTimer.start();
    }

    /*! 隐藏弹层。 */
    function hide() {
        stoast.opacity = 0;
        if(showAnimation.running){
            showAnimation.stop();
        }
        if(hideAnimation.running){
            hideAnimation.stop();
        }

        closeTimer.stop();
    }

}



