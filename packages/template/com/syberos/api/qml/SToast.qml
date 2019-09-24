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

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter

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
            closeTimer.stop()
            if(!hideAnimation.running){
                hideAnimation.start();
                //触发发送结束信号的定时器
                emitSignalTimer.start();
            }
        }
    }

    Timer{
        id: emitSignalTimer
        interval: hideAnimation.duration
        repeat: false
        triggeredOnStart: false

        onTriggered: {
            accepted();
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

        var strlength = getStrLength(title);
        if(icon !== "none" && strlength > 14){
            return "有图标时最多7个汉字长度的文本";
        }

        if(icon === "none" && strlength > 28 ){
            return "无图标时最多显示两行文本（14个汉字长度）";
        }

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
            toastText.text = getOutputStr(title, stoast.textLength);
            stoast.width = stoast.scaleFactor * toastText.contentWidth + 80
            stoast.height = stoast.scaleFactor * toastText.contentHeight + 80
        }

        if(duration){
            if (!(/(^[1-9]\d*$)/.test(duration))) {
                return "duration只能是正整数";
            }
            closeTimer.interval = parseInt(duration) + parseInt(showAnimation.duration);
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

    /*! 获取字符串长度。 */
    function getStrLength(inputStr){
      var currLength = 0
      if (!inputStr) {
        return currLength
      }

      for (var i = 0; i < inputStr.length; i++) {
        var item = inputStr.charAt(i)
        // 中文字符的长度经编码之后大于4
        if (escape(item).length > 4) {
          currLength += 2
        } else {
          currLength += 1
        }
      }
      return currLength
    }


    /*! 获取最终展现字符串。每行14英文字符的长度*/
    function getOutputStr(inputStr, maxRowLength){

        if(!inputStr){
            return "";
        }

        var currLength = 0;
        var outputStr = "";
        var lineBreak = false;
        for(var i = 0; i < inputStr.length; i++){
            var item = inputStr.charAt(i);
            //中文字符的长度经编码之后大于4
            if(escape(item).length > 4){
                currLength += 2;
            }else{
                currLength += 1;
            }
            outputStr = outputStr.concat(item);
            //如果未换行且已达到单行字符串最大长度，则给文本换行
            if(!lineBreak && currLength >= maxRowLength){
                outputStr = outputStr.concat("\n");
                lineBreak = true;
            }
        }

        //如果只有一行，则将换行符去掉
        if(outputStr.indexOf("\n") == outputStr.length-1){
            outputStr = outputStr.replace("\n", "");
        }
        return outputStr;
    }
}



