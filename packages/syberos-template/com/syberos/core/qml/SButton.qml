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

/*!
   \qmltype CButton
   \inqmlmodule com.syberos.basewidgets
   \since 2.0
   \ingroup controls
   \brief 系统按钮

   主要由两部分组成：背景和内容区。内容区包括图标和文字，布局方式为图标在左侧，文字在右侧。使用时可以只给图标或者只给文字，
   也可同时给出图标和文字。系统默认的CButton只有文字，没有图标，外观如下：

   \image cbutton_all.png

   示例代码:
   \qml
   CButton {
       iconSource: "your url"
       text: "some text"
   }
   \endqml
*/

MouseArea {
   id: button

//   implicitWidth: labelItemLoader.implicitWidth + implicitHorizontalPadding
//   implicitHeight: labelItemLoader.implicitHeight + implicitVerticalPadding
   implicitWidth: labelItemLoader.implicitWidth
   implicitHeight: labelItemLoader.implicitHeight
   opacity: enabled ? (button.pressed ? 0.5 : 1) : 0.5

   /*! 默认垂直方向内容区域与边界的距离。如果设置了高度，则此不起作用 */
   property int implicitVerticalPadding:20

   /*! 默认水平方向内容区域与边界的距离。如果设置了宽度，则此不起作用 */
   property int implicitHorizontalPadding:30

   /*! 是否显示背景 */
   property bool backgroundEnabled: true

   /*! 图标url */
   property url iconSource: ""

   /*! labelItem水平方向上的偏移量，数值小于0，向左偏移, 反之向右偏移。*/
   property int labelHorizontalOffset: 0

   /*! labelItem竖直方向上的偏移量，数值小于0，向上偏移, 反之向下偏移。 */
   property int labelVerticalOffset: 0

   /*! 文本字体大小 */
   property real pixelSize: gUiConst.getValue("S3")

   /*! 图片和文本间距 */
   property int spacing: (button.iconSource != "" && button.text != "") ? 10 : 0   //控制文字与元素间距

   /*! 文本内容 */
   property string text: ""

   /*! 文本颜色 */
   property string textColor: "#007aff"
   /*!
       \qmlproperty object CButton::backgroundItem
       backgroundComponent加载完成之后对应的Item元素。
   */
   property alias backgroundItem: backgroundLoader.item

   /*! 背景组件，用于定制按钮的背景样式。 */
   property Component backgroundComponent: Item {
       Rectangle {
           anchors.centerIn: parent
           anchors.fill: parent
           color: "transparent"
       }
   }

   /*!
       \qmlproperty object CButton::labelItem
       labelComponent加载完成之后对应的Item元素。
   */
   property alias labelItem:labelItemLoader.item

   /*! 内容区组件，用于定制按钮的内容标示。 */
   property Component labelComponent: Row {
       spacing:button.spacing
       Image {
           id: icon
           source: button.iconSource
           anchors.verticalCenter: parent.verticalCenter
       }

       Text {
           id: text
           anchors.verticalCenter: parent.verticalCenter
           font.pixelSize: button.pixelSize
           color: button.textColor
           text: button.text
       }
   }

   Loader {
       id: backgroundLoader
       anchors.fill: parent
       sourceComponent: backgroundComponent
       active: button.backgroundEnabled
       z:-1
   }

   Loader {
       id: labelItemLoader
       sourceComponent: labelComponent
       anchors.centerIn: parent
       anchors.horizontalCenterOffset: button.labelHorizontalOffset
       anchors.verticalCenterOffset: button.labelVerticalOffset
   }
}
