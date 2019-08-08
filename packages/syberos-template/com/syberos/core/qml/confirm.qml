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

/*!
   \qmltype CDialog
   \inqmlmodule com.syberos.basewidgets
   \since 2.0
   \ingroup controls
   \brief 默认对话框控件

   CDialog主要由五个部分组成：背景区，对话框背景区，标题区，内容区，按钮区。
   其中浮层背景不可定制，其余部分可根据用户需求自行定制。
   定制方法可以参考 \l{SyberOS Controls Customization}{控件的定制}。
   控件结构示意：

   \raw HTML
   <div style="margin:10px;display:block;border:1px solid #999;width:360px;height:640px;background:#555;">
       <div style="margin:2px;width:356px;height:398px;text-align:center;">
           <span style="color:#fff;line-height:300px;">背景区</span>
       </div>
       <div style="height:238px;background:#fff;">
           <div style="width:356px; height:25px;">
               <span style="margin-left:10px;line-height:40px">对话框背景区</span>
           </div>
           <div style="margin:10px;width:340px; height:40px;background:#ddd;text-align:center;">
               <span style="line-height:40px">标题区</span>
           </div>
           <div style="margin:10px;width:340px; height:96px;background:#bbb;text-align:center;">
               <span style="line-height:90px">内容区</span>
           </div>
           <div style="margin:10px;width:340px; height:40px;background:#ddd;text-align:center;">
               <span style="line-height:40px">按钮区</span>
           </div>
       </div>
   </div>
   \endraw

   控件外观：
   \image cdialog.png

   示例代码:
   \qml
   CDialog {
       id: dialog
       titleText: "message title"
       messageText: "message content"
   }
   \endqml
*/

CAbstractPopLayer{
   id:cdialog
   anchors.fill: parent

   /*! 标题区与对话框背景区上边沿之间的距离。 */
   property int topSpacing: 60

   /*! 标题区和内容区之间的距离。 */
   property int spacingBetweenTitleAreaAndMessageArea: 60

   /*!  内容区和按钮区之间的距离。*/
   property int spacingBetweenMessageAreaAndButtonArea: 60

   /*! 内容区与底部之间距离。*/
   property int bottomSpacing:40

   /*! 标题文本。 */
   property string titleText: ""

   /*! 标题颜色。 */
   property color titleTextColor: gUiConst.getValue("CT1")

   /*! 标题字体大小。 */
   property int titleTextPixelSize: gUiConst.getValue("S1")

   /*! 标题区左侧边距。*/
   property int titleAreaLeftMargin: 40

   /*! 标题区右侧边距。*/
   property int titleAreaRightMargin:40

   /*!
       \qmlproperty Component CDialog::titleAreaComponent
       标题区样式组件，默认为Text
   */
   property alias titleAreaComponent:titleAreaLoader.sourceComponent

   /*!
       \qmlproperty object CDialog::titleAreaItem
       titleAreaComponent加载完成之后对应的Item元素
   */
   readonly property alias titleAreaItem:titleAreaLoader.item

   /*!
       \qmlproperty bool CDialog::titleAreaEnabled
       是否启用标题区。
   */
   property alias titleAreaEnabled:titleAreaLoader.active

   // MessageAra使用相关属性

   /*! 内容区文本。 */
   property string messageText: ""

   /*! 内容区文本颜色。 */
   property color messageTextColor: gUiConst.getValue("CT1")

   /*! 内容区文本字体大小。 */
   property int messageTextPixelSize: gUiConst.getValue("S3")

   /*! 内容区左侧边距。 */
   property int messageAreaLeftMargin: 70

   /*! 内容区右侧边距。 */
   property int messageAreaRightMargin: 70

   /*!
       \qmlproperty Component CDialog::messageAreaComponent
       内容区组件，默认为Text。
   */
   property alias messageAreaComponent:messageAreaLoader.sourceComponent

   /*!
       \qmlproperty object CDialog::messageAreaItem
       messageAreaComponent加载完成之后对应的Item元素。
   */
   property alias messageAreaItem:messageAreaLoader.item

   /*!
       \qmlproperty bool CDialog::messageAreaEnabled
       内容区是否加载。
   */
   property alias messageAreaEnabled: messageAreaLoader.active

   // Button区域属性设置相关

   /*! 取消按钮文本，默认为“取消”。 */
   property string rejectButtonText: os.i18n.ctr(qsTr("Cancel"))

   /*! 确认按钮文本，默认为“确定”。 */
   property string acceptedButtonText: os.i18n.ctr(qsTr("Ok"))

   /*! 确认按钮是否启用。 */
   property bool acceptButtonEnabled:true

   /*! 按钮区按钮之间的距离。*/
   property int buttonAreaSpacing:40

   /*! 按钮区左侧边距。*/
   property int buttonAreaLeftMargin: 80

   /*! 按钮区右侧边距。 */
   property int buttonAreaRightMargin: 80

   /*! 按钮区按钮的高度。*/
   property int buttonHeight: 90

   /*!
       \qmlproperty Component CDialog::buttonAreaComponent
       按钮区组件。
   */
   property alias buttonAreaComponent:buttonAreaLoader.sourceComponent

   /*!
       \qmlproperty Component CDialog::buttonAreaComponent
       对话框内容背景区自定义样式接口。
       其高度会随着dialog的标题区、内容区、按键区以及区域之间的距离属性值的变化自动变化。因此高度等属性不可定制。
   */
   property alias dialogContentAreaComponent: dialogContentAreaLoader.sourceComponent

   /*!
       \qmlproperty object CDialog::buttonAreaItem
       buttonAreaComponent加载完成之后对应的Item元素。
   */
   property alias buttonAreaItem:buttonAreaLoader.item

   /*!
       \qmlproperty bool CDialog::buttonAreaEnabled
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
       color: gUiConst.getValue("CB2")
       opacity: 0
       z:-1
   } /*! end of Rectangle */

   /*! 对话框背景，不允许定制 */
   MouseArea{
       id:contentBackground
       anchors.top:parent.bottom
       width:parent.width
       height:contentHeight()

       Loader{
           id: dialogContentAreaLoader
           anchors.fill: parent
           sourceComponent: Item{
               Rectangle{
                   anchors.fill: parent
                   color: gUiConst.getValue("CB1")
                   radius: 50
               }
               Rectangle{
                   height:60
                   anchors.bottom: parent.bottom
                   color: gUiConst.getValue("CB1")
                   width:parent.width
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

           h += bottomSpacing
           h += topSpacing
           return h
       }
   }

   Loader{
       id:titleAreaLoader
       anchors.top:parent.bottom
       anchors.left: parent.left
       anchors.leftMargin: titleAreaLeftMargin
       anchors.right: parent.right
       anchors.rightMargin: titleAreaRightMargin
       sourceComponent: Text{
           font.pixelSize: cdialog.titleTextPixelSize
           color:cdialog.titleTextColor
           text:cdialog.titleText
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           elide: Text.ElideRight
       }
   }

   Loader{
       id:messageAreaLoader
       anchors.top:parent.bottom
       anchors.left: parent.left
       anchors.leftMargin: messageAreaLeftMargin
       anchors.right: parent.right
       anchors.rightMargin: messageAreaRightMargin
       sourceComponent: Text{
           font.pixelSize: cdialog.messageTextPixelSize
           color:cdialog.messageTextColor
           text:cdialog.messageText
           wrapMode:Text.WrapAnywhere;
           horizontalAlignment: lineCount<=1 ? Text.AlignHCenter:Text.AlignLeft
       }
   }

   Loader{
       id:buttonAreaLoader
       anchors.top:parent.bottom
       anchors.left: parent.left
       anchors.leftMargin: buttonAreaLeftMargin
       anchors.right: parent.right
       anchors.rightMargin: buttonAreaRightMargin
       sourceComponent:Item{
           implicitHeight:buttonsRow.implicitHeight
           property int buttonWidth:(buttonAreaLoader.width - buttonsRow.spacing) / 2
           Row{
               id:buttonsRow
               spacing: buttonAreaSpacing
               anchors.centerIn: parent
               enabled: !animating
               CButton{
                   id:rejectButton
                   text:cdialog.rejectButtonText
                   width:buttonWidth
                   height: cdialog.buttonHeight
                   onClicked:{
                       hideAnimation.rejectedFlag = true
                       cdialog.hide()
                   }
               }
               CButton{
                   id:acceptButton
                   text:cdialog.acceptedButtonText
                   width:buttonWidth
                   height: cdialog.buttonHeight
                   enabled: acceptButtonEnabled
                   onClicked:{
                       hideAnimation.acceptedFlag = true
                       cdialog.hide()
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
           if(gAppUtils.lastDialog() && gAppUtils.lastDialog().visible && gAppUtils.lastDialog() != cdialog ) {
               gAppUtils.setDialogWaitToShow(true)
               return gAppUtils.lastDialog().hide()
           }
           if(!running){
               start()
           }
       }

       NumberAnimation { target: background; property: "opacity"; duration: gSystemUtils.durationRatio*300; to: cdialog.__backGroundOpacity }
       SequentialAnimation{
           PauseAnimation { duration:  gSystemUtils.durationRatio*25 }
           NumberAnimation {
               target:contentBackground; property:"anchors.topMargin"; duration: gSystemUtils.durationRatio*300;
               easing.type: Easing.OutCubic; to: -contentBackground.height
           }
           ScriptAction{ script: contentBackground.anchors.topMargin = Qt.binding(function(){return -contentBackground.height}) }
       }
       SequentialAnimation{
           PauseAnimation { duration:  gSystemUtils.durationRatio*50 }
           NumberAnimation {
               target: titleAreaLoader; property:"anchors.topMargin"; duration: gSystemUtils.durationRatio*250;
               easing.type: Easing.OutCubic;  to: -(contentBackground.height - topSpacing)
           }
           ScriptAction{ script: titleAreaLoader.anchors.topMargin = Qt.binding(function(){return -(contentBackground.height - topSpacing)}) }
       }
       SequentialAnimation{
           PauseAnimation { duration:  gSystemUtils.durationRatio*75}
           NumberAnimation { target: messageAreaLoader; property:"anchors.topMargin"; duration: gSystemUtils.durationRatio*250; easing.type: Easing.OutCubic; to: {
                   if(titleAreaEnabled) {
                       return -(contentBackground.height - topSpacing - titleAreaLoader.height - spacingBetweenTitleAreaAndMessageArea)
                   } else {
                       return -(contentBackground.height - topSpacing)
                   }
               }
           }
           ScriptAction{ script: messageAreaLoader.anchors.topMargin = Qt.binding(function(){
               if(titleAreaEnabled) {
                   return -(contentBackground.height - topSpacing - titleAreaLoader.height - spacingBetweenTitleAreaAndMessageArea)
               } else {
                   return -(contentBackground.height - topSpacing)
               }})
           }
       }
       SequentialAnimation{
           PauseAnimation { duration:  gSystemUtils.durationRatio*100}
           NumberAnimation {
               target: buttonAreaLoader; property:"anchors.topMargin"; duration: gSystemUtils.durationRatio*250;
               easing.type: Easing.OutCubic; to: -(bottomSpacing +  buttonAreaLoader.height)
           }
           ScriptAction{ script: buttonAreaLoader.anchors.topMargin = Qt.binding(function(){return -(bottomSpacing +  buttonAreaLoader.height)}) }
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

       NumberAnimation { target: buttonAreaLoader; property:"anchors.topMargin"; duration: gSystemUtils.durationRatio*250; to: 0;  easing.type: Easing.OutCubic }
       SequentialAnimation{
           NumberAnimation { target: messageAreaLoader; property:"anchors.topMargin"; duration: gSystemUtils.durationRatio*250; to: 0; easing.type: Easing.OutCubic }
           PauseAnimation { duration: gSystemUtils.durationRatio*250}
           ScriptAction{ script: buttonAreaLoader.anchors.topMargin = 0 }
           ScriptAction{ script: messageAreaLoader.anchors.topMargin = 0 }
       }
       SequentialAnimation{
           NumberAnimation { target: titleAreaLoader; property:"anchors.topMargin"; duration: gSystemUtils.durationRatio*250; to: 0; easing.type: Easing.OutCubic }
           PauseAnimation { duration: gSystemUtils.durationRatio*250}
           ScriptAction{ script: titleAreaLoader.anchors.topMargin = 0 }
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
       if((showAnimating || showDelayTimer.running || cdialog.visible) && !hideDelayTimer.running){
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
               if(!cdialog.visible){
                   cdialog.visible = true
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
           if((cdialog.visible && !showDelayTimer.running && !showAnimation.running) || times > 20){
               hideDelayTimer.stop()
               hideAnimation.show()
               times = 0
           }
           ++times
       }
   }
}
