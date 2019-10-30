/*!
* This file is part of hybrid-core
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*
*   xuejun <xuejun@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

import QtQuick 2.3
import QtQuick.Window 2.2
import com.syberos.basewidgets 2.0



CAbstractPopLayer{
   id:sconfirm
   anchors.fill: parent

   /*! 点击mask是否关闭 */
   canceledOnOutareaClicked: false

   /*! 点击返回键是否隐藏弹层，默认值为false*/
   canceledOnBackKeyReleased: false

   /*! 模态框和页面的缩放比例 */
   property real scaleFactor: Screen.width / 1080

   /*! 模态框背景的宽度 */
   property real contentBgWidth: 840 * scaleFactor

   /*! 标题区与对话框背景区上边沿之间的距离 */
   property real topSpacing: 80 * scaleFactor

   /*! 无标题的时候，内容区与对话框背景区上边沿之间的距离 */
   property real topSpacingNoTitle: 120 * scaleFactor //120

   /*! 对话框的圆角大小 */
   property real radius: 6

   /*! 标题区和内容区之间的距离 */
   property real spacingBetweenTitleAreaAndMessageArea: 80 * scaleFactor

   /*! 内容区和按钮区之间的距离(减掉文字的行高和实际自体的大小差距 messageTextPixelSize messageTextLineHeight)*/
   property real spacingBetweenMessageAreaAndButtonArea: (100 - (70 - 40)) * scaleFactor

   /*! 标题文本 */
   property string titleText: ""

   /*! 标题颜色 */
   property color titleTextColor: "#333333"

   /*! 标题smallIcon的宽度 */
   property real titleSmallIconWidth: 54 * scaleFactor

   /*! 标题BigIcon的宽度 */
   property real titleBigIconWidth: 212 * scaleFactor

   /*! 标题字体大小 */
   property real titleTextPixelSize: 52 * scaleFactor

   /*! 标题区左侧边距*/
   property int titleAreaHeight: 100 * scaleFactor

   /*! 标题区左侧边距*/
   property real titleAreaLeftMargin: 40 * scaleFactor

   /*! 标题区右侧边距*/
   property real titleAreaRightMargin:40 * scaleFactor

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
       是否启用标题区
   */
   property alias titleAreaEnabled:titleAreaLoader.active

   /*! 标题左侧icon，目前不支持定制，属于内置模块，有warning 和 success */
   property string icon: ""

   /*! 标题左侧icon warning */
   property string warningType: "warning"

   /*! 标题左侧icon success */
   property string successType: "success"

   /*! 标题左侧 warning icon */
   property string warningIcon: "qrc:/com/syberos/api/res/warning.png"

   /*! 标题左侧 success icon */
   property string successIcon: "qrc:/com/syberos/api/res/success_primary.png"

   /*! 无标题 大 warning icon */
   property string warningBigIcon: "qrc:/com/syberos/api/res/warning_big.png"

   /*! 无标题 大 success icon */
   property string successBigIcon: "qrc:/com/syberos/api/res/success_primary_big.png"

   /*! 是否正确的IconType */
   property bool hasIconType: icon === warningType || icon === successType

   // MessageAra使用相关属性

   /*! 内容区文本 */
   property string messageText: ""

   /*! 内容区文本颜色 */
   property color messageTextColor: "#333333"


   /*! 内容区文本字体大小 */
   property real messageTextPixelSize: 40 * scaleFactor

   /*! 内容区文本行高大小 */
   property real messageTextLineHeight: 70 * scaleFactor

   /*! 内容区左侧边距 */
   property real messageAreaLeftMargin: 70 * scaleFactor

   /*! 内容区右侧边距 */
   property real messageAreaRightMargin: 70 * scaleFactor

   /*!
       \qmlproperty Component SConfirm::messageAreaComponent
       内容区组件，默认为Text
   */
   property alias messageAreaComponent:messageLoaderArea.sourceComponent

   /*!
       \qmlproperty object SConfirm::messageAreaItem
       messageAreaComponent加载完成之后对应的Item元素
   */
   property alias messageAreaItem:messageLoaderArea.item

   /*!
       \qmlproperty bool SConfirm::messageAreaEnabled
       内容区是否加载
   */
   property alias messageAreaEnabled: messageLoaderArea.active

   // Button区域属性设置相关

   /*! 取消按钮文本，默认为“取消” */
   property string rejectButtonText: qsTr("取消")

   /*! 确认按钮文本，默认为“确定” */
   property string acceptedButtonText: qsTr("确定")

   /*! 取消按钮是否展示 */
   property bool rejectButtonVisible: true

   /*! 确认按钮是否启用 */
   property bool acceptButtonEnabled: true

   /*! 确认按钮的颜色 */
   property color acceptButtonColor: "#007aff"

   /*! 取消按钮的颜色 */
   property color rejectButtonColor: "#666666"


   /*! 按钮区按钮之间的距离/按钮区按钮分割线的宽度*/
   property real buttonAreaSpacing: 2 * scaleFactor

   /*! 确认按钮加载状态 */
   property bool acceptButtonLoading: false

   /*! 按钮区左侧边距*/
   property real buttonAreaLeftMargin: 80 * scaleFactor

   /*! 按钮区右侧边距 */
   property real buttonAreaRightMargin: 80 * scaleFactor

   /*! 按钮区按钮的高度*/
   property real buttonHeight: 180 * scaleFactor

   /*! 按钮区按钮分割线的颜色*/
   property string buttonLineColor: "#cccccc"

   /*! 按钮区按钮的字体大小 */
   property real buttonTextPixelSize: 48 * scaleFactor

   /*! 模态框滑动到屏幕中间需要的距离 */
   property real distance: (contentBackground.contentHeight() / 2 + parent.height / 2) * scaleFactor

   /*!
       \qmlproperty Component SConfirm::buttonAreaComponent
       按钮区组件
   */
   property alias buttonAreaComponent:buttonAreaLoader.sourceComponent

   /*!
       \qmlproperty Component SConfirm::buttonAreaComponent
       对话框内容背景区自定义样式接口
       其高度会随着dialog的标题区、内容区、按键区以及区域之间的距离属性值的变化自动变化, 因此高度等属性不可定制
   */
   property alias dialogContentAreaComponent: dialogContentAreaLoader.sourceComponent

   /*!
       \qmlproperty object SConfirm::buttonAreaItem
       buttonAreaComponent加载完成之后对应的Item元素
   */
   property alias buttonAreaItem:buttonAreaLoader.item

   /*!
       \qmlproperty bool SConfirm::buttonAreaEnabled
       按钮区是否加载
   */
   property alias buttonAreaEnabled:buttonAreaLoader.active

   /*! \internal 控制背景透明度 */
   property real __backGroundOpacity: 0.73

   /*! 标识动画是否正在进行，只读属性*/
   readonly property bool animating: showAnimation.running || hideAnimation.running

   /*! 拒绝信号，当点击默认的“取消”按钮时发射 */
   signal rejected()

   /*! 接受信号，当点击默认的“确定”按钮时发射 */
   signal accepted()

   // 点击返回键触发取消事件
   onBackKeyReleased: {
       // 有取消按钮才可以按返回键触发取消时间, alert不能取消
       if (rejectButtonVisible) {
           hideAnimation.rejectedFlag = true
           sconfirm.hide()
       }
   }

   // 多指操作，为了解决bug， 一个手指长按内容区域，另一个手指滑动背景层，这里不做处理就可以， 否则页面退出后就崩溃了
   MultiPointTouchArea {
       anchors.fill: parent
       touchPoints: [
           TouchPoint { id: point1 },
           TouchPoint { id: point2 }
       ]
   }

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
       width: contentBgWidth
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
                   color: "transparent"
                   width:parent.width
                   radius: sconfirm.radius
               }
           }
       }

       /*! 计算对话框背景高度 */
       function contentHeight(){
           var h = 0
           if(titleAreaEnabled) {
               h += topSpacing
               h += titleAreaLoader.height
               if(messageAreaEnabled || buttonAreaEnabled)
                   h += spacingBetweenTitleAreaAndMessageArea
           } else {
               h += topSpacingNoTitle
           }
           if(messageAreaEnabled) {
               h += messageLoaderArea.height
               if(buttonAreaEnabled)
                   h += spacingBetweenMessageAreaAndButtonArea
           }
           if(buttonAreaEnabled) {
               h += buttonAreaLoader.height
           }


           return h
       }
   }


   Loader{
       id:titleAreaLoader
       active: titleText || hasIconType
       anchors.top:contentBackground.top
       anchors.topMargin: titleAreaEnabled ? topSpacing : topSpacingNoTitle
       anchors.left: contentBackground.left
       anchors.leftMargin: titleAreaLeftMargin
       anchors.right: contentBackground.right
       anchors.rightMargin: titleAreaRightMargin
       sourceComponent: Rectangle {
           color: 'transparent'
           width: hasIconType && !titleText ? titleBigIconWidth : titleSmallIconWidth
           height: hasIconType && !titleText ? titleBigIconWidth : titleSmallIconWidth

           property real hasIconLeftMargin: (titleAreaLoader.width - textcontent.contentWidth - titleSmallIconWidth) / 2
           property real noIconLeftMargin: (titleAreaLoader.width - textcontent.contentWidth) / 2


           Row {
               id: titleRow
               visible: titleText !== ''
               anchors.left: parent.left
               anchors.leftMargin: hasIconType ? hasIconLeftMargin : noIconLeftMargin
               spacing: 10
               Image {
                   visible: hasIconType
                   anchors.topMargin: - (titleSmallIconWidth - textcontent.height) / 2
                   source:  icon === warningType ? warningIcon : icon === successType ? successIcon : ''
               }
               Text{
                   id:textcontent
                   anchors.verticalCenter: parent.verticalCenter
                   font.pixelSize: sconfirm.titleTextPixelSize
                   color:sconfirm.titleTextColor
                   text:sconfirm.titleText
                   elide: Text.ElideRight
               }
           }


           Image {
               visible: !titleText && hasIconType
               width: titleBigIconWidth
               height: titleBigIconWidth
               anchors.horizontalCenter: parent.horizontalCenter
               source:  icon === warningType ? warningBigIcon : icon === successType ? successBigIcon : ''
           }

       }

   }


   Loader{
       id:messageLoaderArea
       anchors.topMargin: titleAreaEnabled ? spacingBetweenTitleAreaAndMessageArea : topSpacingNoTitle
       anchors.top: titleAreaEnabled ? titleAreaLoader.bottom : contentBackground.top
       anchors.left: contentBackground.left
       anchors.leftMargin: messageAreaLeftMargin
       anchors.right: contentBackground.right
       anchors.rightMargin: messageAreaRightMargin
       sourceComponent: Text {
           id: messageText
           font.pixelSize: sconfirm.messageTextPixelSize
           color:sconfirm.messageTextColor
           lineHeight: sconfirm.messageTextLineHeight
           lineHeightMode: Text.FixedHeight
           text:sconfirm.messageText
           wrapMode:Text.WrapAnywhere
           horizontalAlignment: lineCount<=1 ? Text.AlignHCenter:Text.AlignLeft
        }
   }

   Loader{
       id:buttonAreaLoader
       anchors.top:messageLoaderArea.bottom
       anchors.topMargin: spacingBetweenMessageAreaAndButtonArea
       anchors.left: contentBackground.left
       anchors.right: contentBackground.right
       sourceComponent: Rectangle {
           color: 'transparent'

           implicitHeight: buttonsRow.implicitHeight + buttonAreaSpacing
           property int buttonWidth:(buttonAreaLoader.width - buttonsRow.spacing) / 2 - buttonsRow.spacing
           clip: true

           Rectangle {
               id:line
                width: buttonAreaLoader.width
                height: buttonAreaSpacing
                color: sconfirm.buttonLineColor

                Row{
                    id:buttonsRow
                    spacing: buttonAreaSpacing
                    anchors.top: line.bottom
                    enabled: !animating

                    SButton{
                        id:rejectButton
                        visible: sconfirm.rejectButtonVisible
                        text:sconfirm.rejectButtonText
                        width: buttonWidth
                        height: sconfirm.buttonHeight
                        textColor: rejectButtonColor ? rejectButtonColor : rejectButton.textSecondColor
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
                        visible: !acceptButtonLoading
                        text:sconfirm.acceptedButtonText
                        width: sconfirm.rejectButtonVisible ? buttonWidth : buttonAreaLoader.width
                        height: sconfirm.buttonHeight
                        enabled: acceptButtonEnabled
                        pixelSize: sconfirm.buttonTextPixelSize
                        textColor: acceptButtonColor ? acceptButtonColor : acceptButton.textHrefColor

                        onClicked:{
                            hideAnimation.acceptedFlag = true
                            sconfirm.hide()
                        }
                    }
                    Rectangle {
                        visible: acceptButtonLoading
                        width: buttonWidth - buttonAreaSpacing
                        height: sconfirm.buttonHeight

                        SCollisionIndicator {
                            implicitWidth: buttonWidth
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            running: acceptButtonLoading
                        }
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
       SequentialAnimation {
           NumberAnimation { target: contentBackground; property:"opacity"; duration: gSystemUtils.durationRatio*300; to: 1}
       }
       SequentialAnimation {
           NumberAnimation { target: titleAreaLoader; property:"opacity"; duration: gSystemUtils.durationRatio*300; to: 1}
       }
       SequentialAnimation {
           NumberAnimation { target: messageLoaderArea; property:"opacity"; duration: gSystemUtils.durationRatio*300; to: 1}
       }
       SequentialAnimation {
           NumberAnimation { target: buttonAreaLoader; property:"opacity"; duration: gSystemUtils.durationRatio*300; to: 1}
       }


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

       SequentialAnimation {
           NumberAnimation { target: background; property:"opacity"; duration: gSystemUtils.durationRatio*300; to: 0}
       }

       SequentialAnimation {
           NumberAnimation { target: contentBackground; property:"opacity"; duration: gSystemUtils.durationRatio*300; to: 0}
       }

       SequentialAnimation {
           NumberAnimation { target: titleAreaLoader; property:"opacity"; duration: gSystemUtils.durationRatio*300; to: 0}
       }
       SequentialAnimation {
           NumberAnimation { target: messageLoaderArea; property:"opacity"; duration: gSystemUtils.durationRatio*300; to: 0}
       }
       SequentialAnimation {
           NumberAnimation { target: buttonAreaLoader; property:"opacity"; duration: gSystemUtils.durationRatio*300; to: 0}
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
           if((messageLoaderArea.status === Loader.Ready) || (times > 30)){
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
