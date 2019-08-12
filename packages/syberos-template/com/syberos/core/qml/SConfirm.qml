/*
 * This file is part of syberos-toolkit-core
 * Copyright (C) 2015 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
 * Authors:
 *       zhao pan <zhaopan@syberos.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
 */

import QtQuick 2.3
import com.syberos.basewidgets 2.0
import QtQuick.Controls 1.4
/*!
   \qmltype SConfirm
   \inqmlmodule com.syberos.basewidgets
   \since 2.0
   \ingroup controls
   \brief 默认对话框控件

   SConfirm主要由五个部分组成：背景区，对话框背景区，标题区，内容区，按钮区。
   其中浮层背景不可定制，其余部分可根据用户需求自行定制。

   控件外观：
   \image SConfirm.png

   示例代码:
   \qml
   SConfirm {
       id: dialog
       titleText: "message title"
       messageText: "message content"
   }
   \endqml
*/



CAbstractPopLayer{
   id:sconfirm
   anchors.fill: parent

   /*!模态框和页面的宽度比例。 */
   property real proportion: 840 / 1080

   /*! 标题区与对话框背景区上边沿之间的距离。 */
   property real topSpacing: 80 * proportion

   /*! 无标题的时候，内容区与对话框背景区上边沿之间的距离。 */
   property real topSpacingNoTitle: 120 * proportion

   /*! 对话框的圆角大小。 */
   property real radius: 6

   /*! 标题区和内容区之间的距离。 */
   property real spacingBetweenTitleAreaAndMessageArea: 80 * proportion

   /*!  内容区和按钮区之间的距离。*/
   property real spacingBetweenMessageAreaAndButtonArea: 100 * proportion

   /*! 标题文本。 */
   property string titleText: ""

   /*! 标题颜色。 */
   property color titleTextColor: "#333333"

   /*! 标题字体大小。 */
   property real titleTextPixelSize: 52 * proportion

   /*! 标题区左侧边距。*/
   property int titleAreaHeight: 100 * proportion

   /*! 标题区左侧边距。*/
   property real titleAreaLeftMargin: 40 * proportion

   /*! 标题区右侧边距。*/
   property real titleAreaRightMargin:40 * proportion

   /*!
       \qmlproperty Component SConfirm::titleAreaComponent
       标题区样式组件，默认为Text
   */
   property alias titleAreaComponent:titleAreaLoader.sourceComponent

   /*!
       \qmlproperty object SConfirm::titleAreaItem
       titleAreaComponent加载完成之后对应的Item元素
   */
   readonly property alias titleAreaItem:titleAreaLoader.item

   /*!
       \qmlproperty bool SConfirm::titleAreaEnabled
       是否启用标题区。
   */
   property alias titleAreaEnabled:titleAreaLoader.active

   // MessageAra使用相关属性

   /*! 内容区文本。 */
   property string messageText: ""

   /*! 内容区文本颜色。 */
   property color messageTextColor: "#333333"


   /*! 内容区文本字体大小。 */
   property real messageTextPixelSize: 40 * proportion

   /*! 内容区文本行高大小。 */
   property real messageTextLineHeight: 70 * proportion

   /*! 内容区左侧边距。 */
   property real messageAreaLeftMargin: 70 * proportion

   /*! 内容区右侧边距。 */
   property real messageAreaRightMargin: 70 * proportion

   /*!
       \qmlproperty Component SConfirm::messageAreaComponent
       内容区组件，默认为Text。
   */
   property alias messageAreaComponent:messageAreaLoader.sourceComponent

   /*!
       \qmlproperty object SConfirm::messageAreaItem
       messageAreaComponent加载完成之后对应的Item元素。
   */
   property alias messageAreaItem:messageAreaLoader.item

   /*!
       \qmlproperty bool SConfirm::messageAreaEnabled
       内容区是否加载。
   */
   property alias messageAreaEnabled: messageAreaLoader.active

   // Button区域属性设置相关

   /*! 取消按钮文本，默认为“取消”。 */
   property string rejectButtonText: qsTr("取消")

   /*! 确认按钮文本，默认为“确定”。 */
   property string acceptedButtonText: qsTr("确定")

   /*! 取消按钮是否展示。 */
   property bool rejectButtonVisible: true

   /*! 确认按钮是否启用。 */
   property bool acceptButtonEnabled: true

   /*! 按钮区按钮之间的距离/按钮区按钮分割线的宽度。*/
   property real buttonAreaSpacing: 2 * proportion

   /*! 按钮区左侧边距。*/
   property real buttonAreaLeftMargin: 80 * proportion

   /*! 按钮区右侧边距。 */
   property real buttonAreaRightMargin: 80 * proportion

   /*! 按钮区按钮的高度。*/
   property real buttonHeight: 180 * proportion

   /*! 按钮区按钮分割线的颜色。*/
   property string buttonLineColor: "#cccccc"

   /*! 按钮区按钮的字体大小。 */
   property real buttonTextPixelSize: 48 * proportion

   /*! 模态框滑动到屏幕中间需要的距离 */
   property real distance: (contentBackground.contentHeight() / 2 + parent.height / 2) * proportion

   /*!
       \qmlproperty Component SConfirm::buttonAreaComponent
       按钮区组件。
   */
   property alias buttonAreaComponent:buttonAreaLoader.sourceComponent

   /*!
       \qmlproperty Component SConfirm::buttonAreaComponent
       对话框内容背景区自定义样式接口。
       其高度会随着dialog的标题区、内容区、按键区以及区域之间的距离属性值的变化自动变化。因此高度等属性不可定制。
   */
   property alias dialogContentAreaComponent: dialogContentAreaLoader.sourceComponent

   /*!
       \qmlproperty object SConfirm::buttonAreaItem
       buttonAreaComponent加载完成之后对应的Item元素。
   */
   property alias buttonAreaItem:buttonAreaLoader.item

   /*!
       \qmlproperty bool SConfirm::buttonAreaEnabled
       按钮区是否加载。
   */
   property alias buttonAreaEnabled:buttonAreaLoader.active

   /*! \internal 控制背景透明度 */
   property real __backGroundOpacity: 0.73

   /*! 标识动画是否正在进行，只读属性。*/
   readonly property bool animating: showAnimation.running || hideAnimation.running

   /*! 拒绝信号，当点击默认的“取消”按钮时发射。 */
   signal rejected()

   /*! 接受信号，当点击默认的“确定”按钮时发射。 */
   signal accepted()

   /*! 背景, 不允许定制 */
   Rectangle{
       id:background
       anchors.fill: parent
       color: "#000000"
       opacity: 0
       z:-1
   } /*! end of Rectangle */

   /*! 对话框背景，不允许定制 */
   MouseArea{
       id:contentBackground
       anchors.centerIn: parent
       width: proportion * parent.width
       height:contentHeight()

       Loader{
           id: dialogContentAreaLoader
           anchors.fill: parent
           sourceComponent: Item{
               Rectangle{
                   anchors.fill: parent
                   color: "#ffffff"
                   radius: sconfirm.radius
               }
               Rectangle{
                   height:buttonHeight
                   anchors.bottom: parent.bottom
                   color: "#ffffff"
                   width:parent.width
                   radius: sconfirm.radius
               }
           }
       }

       /*! 计算对话框背景高度 */
       function contentHeight(){
           var h = 0
           if(titleAreaEnabled) {
               h += titleAreaLoader.height
               if(messageAreaEnabled || buttonAreaEnabled)
                   h += spacingBetweenTitleAreaAndMessageArea
           }
           if(messageAreaEnabled) {
               h += messageAreaLoader.height
               if(buttonAreaEnabled)
                   h += spacingBetweenMessageAreaAndButtonArea
           }
           if(buttonAreaEnabled) {
               h += buttonAreaLoader.height
           }


           h += topSpacing
           return h
       }
   }

   Loader{
       id:titleAreaLoader
       anchors.top:contentBackground.top
       anchors.topMargin: spacingBetweenTitleAreaAndMessageArea
       anchors.left: contentBackground.left
       anchors.leftMargin: titleAreaLeftMargin
       anchors.right: contentBackground.right
       anchors.rightMargin: titleAreaRightMargin
       sourceComponent: Text{
           font.pixelSize: sconfirm.titleTextPixelSize
           color:sconfirm.titleTextColor
           text:sconfirm.titleText
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           elide: Text.ElideRight
       }
   }

   Loader{
       id:messageAreaLoader
       anchors.topMargin: spacingBetweenMessageAreaAndButtonArea
       anchors.top: titleAreaLoader.bottom
       anchors.left: contentBackground.left
       anchors.leftMargin: messageAreaLeftMargin
       anchors.right: contentBackground.right
       anchors.rightMargin: messageAreaRightMargin
       sourceComponent: Text{
           font.pixelSize: sconfirm.messageTextPixelSize
           color:sconfirm.messageTextColor
           lineHeight: sconfirm.messageTextLineHeight
           lineHeightMode: Text.FixedHeight
           text:sconfirm.messageText
           wrapMode:Text.WrapAnywhere;
           horizontalAlignment: lineCount<=1 ? Text.AlignHCenter:Text.AlignLeft
       }

   }

   Loader{
       id:buttonAreaLoader
       anchors.top:messageAreaLoader.bottom
       anchors.topMargin: spacingBetweenTitleAreaAndMessageArea
       anchors.left: contentBackground.left
//       anchors.leftMargin: buttonAreaLeftMargin
       anchors.right: contentBackground.right
//       anchors.rightMargin: buttonAreaRightMargin
       sourceComponent: Rectangle {
           implicitHeight:buttonsRow.implicitHeight
           property int buttonWidth:(buttonAreaLoader.width - buttonsRow.spacing) / 2 - buttonsRow.spacing

           Rectangle {
                width: buttonAreaLoader.width
                height: buttonAreaSpacing
                color: sconfirm.buttonLineColor
           }
           Row{
               id:buttonsRow
               spacing: buttonAreaSpacing
               anchors.centerIn: parent
               enabled: !animating

               SButton{
                   id:rejectButton
                   visible: sconfirm.rejectButtonVisible
                   text:sconfirm.rejectButtonText
                   width: buttonWidth
                   height: sconfirm.buttonHeight
                   pixelSize: sconfirm.buttonTextPixelSize

                   onClicked:{
                       hideAnimation.rejectedFlag = true
                       sconfirm.hide()
                   }
               }

               Rectangle {
                    visible: sconfirm.rejectButtonVisible
                    width: buttonAreaSpacing
                    height: sconfirm.buttonHeight
                    color: sconfirm.buttonLineColor
               }

               SButton{
                   id:acceptButton
                   text:sconfirm.acceptedButtonText
                   width: sconfirm.rejectButtonVisible ? buttonWidth : buttonAreaLoader.width
                   height: sconfirm.buttonHeight
                   enabled: acceptButtonEnabled
                   pixelSize: sconfirm.buttonTextPixelSize

                   onClicked:{
                       hideAnimation.acceptedFlag = true
                       sconfirm.hide()
                   }
               }
           }
       }
   }

   ParallelAnimation {
       id: showAnimation

       alwaysRunToEnd: true

       function show(){

           if(hideAnimation.running){
               hideAnimation.stop()
           }
           if(gAppUtils.lastDialog() && gAppUtils.lastDialog().visible && gAppUtils.lastDialog() != sconfirm ) {
               gAppUtils.setDialogWaitToShow(true)
               return gAppUtils.lastDialog().hide()
           }
           if(!running){
               start()
           }
       }

       NumberAnimation { target: background; property: "opacity"; duration: gSystemUtils.durationRatio*300; to: sconfirm.__backGroundOpacity }

       onRunningChanged: {
           if(!running){
               showFinished()
           }
       }
   }

   ParallelAnimation {
       id: hideAnimation

       alwaysRunToEnd: true

       property bool acceptedFlag: false
       property bool rejectedFlag: false

       function show(){
           if(showAnimation.running){
               showAnimation.stop()
           }
           if(!running){
               start()
           }
       }


       SequentialAnimation{
           PauseAnimation { duration: gSystemUtils.durationRatio*50 }
           NumberAnimation { target:contentBackground; property:"anchors.topMargin"; duration: gSystemUtils.durationRatio*250; to: 0; easing.type: Easing.OutCubic }
           PauseAnimation { duration: gSystemUtils.durationRatio*250}
           ScriptAction{ script: contentBackground.anchors.topMargin = 0 }
       }
       SequentialAnimation {
           PauseAnimation { duration: gSystemUtils.durationRatio*150 }
           NumberAnimation { target: background; property:"opacity"; duration: gSystemUtils.durationRatio*300; to: 0}
       }
       onRunningChanged: {
           if(!running){
               hideFinished()
               if(acceptedFlag){
                   accepted()
                   acceptedFlag = false
               }
               if(rejectedFlag){
                   rejected()
                   rejectedFlag = false
               }
           }
       }
   }

   onRequestShow:{
       if(!showDelayTimer.running){
           showDelayTimer.start()
       }
   }

   onRequestHide: {
       if((showAnimating || showDelayTimer.running || sconfirm.visible) && !hideDelayTimer.running){
           // 在对话框未显示或者显示timer没有启动的时候表示对话框没有显示，不运行隐藏动画
           hideDelayTimer.start()
       }
   }

   Timer{ // 用于确保信息显示区的界面被加载完成后再进行显示动画
       id: showDelayTimer
       repeat: true
       interval: 20
       //triggeredOnStart: true
       property int times: 0 // 用于保证正常退出循环
       onTriggered: {
           if((messageAreaLoader.status === Loader.Ready) || (times > 30)){
               if(!sconfirm.visible){
                   sconfirm.visible = true
               }
               showDelayTimer.stop()
               showAnimation.show()
               times = 0
           }
           ++times
       }
   }

   Timer{ // 用于避免隐藏动画先于显示动画被调用
       id: hideDelayTimer
       repeat: true
       interval: 30
       property int times: 0 // 用于保证正常退出循环
       onTriggered: {
           if((sconfirm.visible && !showDelayTimer.running && !showAnimation.running) || times > 20){
               hideDelayTimer.stop()
               hideAnimation.show()
               times = 0
           }
           ++times
       }
   }
}
