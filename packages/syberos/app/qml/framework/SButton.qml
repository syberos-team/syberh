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


MouseArea {
   id: button

//   implicitWidth: labelItemLoader.implicitWidth + implicitHorizontalPadding
//   implicitHeight: labelItemLoader.implicitHeight + implicitVerticalPadding
   implicitWidth: labelItemLoader.implicitWidth
   implicitHeight: labelItemLoader.implicitHeight
   opacity: enabled ? (button.pressed ? 0.5 : 1) : 0.5

   /*! 默认垂直方向内容区域与边界的距离, 如果设置了高度，则此不起作用 */
   property real implicitVerticalPadding: env.dp(20)

   /*! 默认水平方向内容区域与边界的距离, 如果设置了宽度，则此不起作用 */
   property real implicitHorizontalPadding: env.dp(30)

   /*! 是否显示背景 */
   property bool backgroundEnabled: true

   /*! 图标url */
   property url iconSource: ""

   /*! labelItem水平方向上的偏移量，数值小于0，向左偏移, 反之向右偏移 */
   property int labelHorizontalOffset: 0

   /*! labelItem竖直方向上的偏移量，数值小于0，向上偏移, 反之向下偏移  */
   property int labelVerticalOffset: 0

   /*! 文本字体大小 */
   property real pixelSize: gUiConst.getValue("S3")

   /*! 图片和文本间距 */
   property real spacing: (button.iconSource != "" && button.text != "") ? env.dp(10) : 0   //控制文字与元素间距

   /*! 文本内容 */
   property string text: ""

   /*! 文本颜色 */
   property color textColor: textHrefColor

   /*! 文本primary颜色 */
   property color textPrimaryColor: "#333333"

   /*! 文本href颜色 */
   property color textHrefColor: "#007aff"

   /*! 文本Second颜色 */
   property color textSecondColor: "#666666"

   /*! 文本third颜色 */
   property color textThirdColor: "#999999"

   /*! 文本four颜色 */
   property color textFourColor: "#bbbbbb"

   /*!
       \qmlproperty object CButton::backgroundItem
       backgroundComponent加载完成之后对应的Item元素
   */
   property alias backgroundItem: backgroundLoader.item

   /*! 背景组件，用于定制按钮的背景样式  */
   property Component backgroundComponent: Item {
       Rectangle {
           anchors.centerIn: parent
           anchors.fill: parent
           color: "transparent"
       }
   }

   /*!
       \qmlproperty object CButton::labelItem
       labelComponent加载完成之后对应的Item元素
   */
   property alias labelItem:labelItemLoader.item

   /*! 内容区组件，用于定制按钮的内容标示  */
   property Component labelComponent: Row {
       id: btnRow
       spacing:button.spacing
       Image {
           id: icon
           source: button.iconSource
           anchors.verticalCenter: btnRow.verticalCenter
       }

       Text {
           id: text
           anchors.verticalCenter: btnRow.verticalCenter
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
