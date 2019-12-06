/*!
* \file CommonTitlebar.qml
* \brief 公共控件，通用标题栏
*
*公共控件，通用标题栏
*
*\author 桓乐乐 huanlele@syberos.com
*\version 1.0
*\date 2015/9/7
*/
import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "../js/util/constants.js" as UI
/*!
  \class CommonTitlebar
  \inModule 公共控件
  \brief 公共控件，通用标题栏
  \ingroup common
  公共控件，通用标题栏
*/

Item{
    id: pageHead
    anchors.top:parent.top
    width: parent.width; height: UI.TITLE_BAR_HEIGHT - gScreenInfo.statusBarHeight
    signal leftItemTriggered()
    signal rightItemFirstTriggered()
    signal rightItemSecondTriggered()
    property bool leftItemEnabled: true
    property bool rightItemEnabled: false
    property bool showRightImg: true
    property alias titleText: centerText.text
    property bool secondRightItemEnabled: true
    property string rightItemFirstImg: ""//"qrc:/res/nav_icon_rfid.png"
    property string rightItemSecondImg: "qrc:/res/nav_icon_qrcode.png"
    property string rightText: "确定"
    Rectangle{
        anchors.fill: parent
        color: "red"
    }
    Item{
        id:leftItem
        visible: leftItemEnabled
        height: parent.height
        width:leftImg.width + 20 *UI.rate
        Image{
            id:leftImg
            anchors.left: parent.left
            anchors.leftMargin: 10 * UI.rate
            anchors.verticalCenter: parent.verticalCenter
            width: visible? sourceSize.width * 0.4 * UI.rate : 0
            height: sourceSize.height * 0.4 * UI.rate 
            source: "qrc:/res/nav_return.png"
            fillMode: Image.PreserveAspectFit
            opacity: mouse.pressed ? 0.5 : 1
        }
        MouseArea{
            id:mouse
            anchors.fill: parent
            onClicked: {
                leftItemTriggered()
            }
        }
    }
    Text{
        id:centerText
        anchors.verticalCenter: parent.verticalCenter
        anchors.left : leftItem.right
        anchors.right: rightItem.left
        anchors.rightMargin: 10 * UI.rate
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        color:"#ffffff"
        font.pixelSize: env.dp(UI.FONT_SIZE_16)
    }
    Item{
        id:rightItem
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: 10 * UI.rate
        visible: rightItemEnabled
        width: visible? (pageHead.showRightImg ? firstImg.width + secondImg.width + 10 : rightTextItem.width)
                      : 0
        Item{
            id:rightTextItem
            visible: !pageHead.showRightImg
            height: parent.height
            width: rightTxt.width + 20 * UI.rate
            Text{
                id:rightTxt
                color:"#ffffff"
                font.pixelSize: UI.FONT_SIZE_16
                anchors.centerIn: parent
                text: pageHead.rightText
            }
            opacity: textMouse.pressed ? 0.5 : 1
            MouseArea{
                id:textMouse
                anchors.fill: parent
                onClicked:rightItemFirstTriggered()
            }
        }

        Image{
            id:firstImg
            visible: pageHead.showRightImg
            width: sourceSize.width * 0.4 * UI.rate
            height: sourceSize.height * 0.4 * UI.rate
            anchors.verticalCenter: parent.verticalCenter
            source: rightItemFirstImg
            fillMode: Image.PreserveAspectFit
            opacity: firstMouse.pressed ? 0.5 : 1
            MouseArea{
                id:firstMouse
                anchors.fill: parent
                onClicked:rightItemFirstTriggered()
            }
        }
        Image{
            id:secondImg
            visible: pageHead.showRightImg && secondRightItemEnabled
            width: visible? sourceSize.width * 0.4 * UI.rate : 0
            height: sourceSize.height * 0.4 * UI.rate
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: firstImg.right
            anchors.leftMargin: 10
            source: rightItemSecondImg
            fillMode: Image.PreserveAspectFit
            opacity: secMouse.pressed ? 0.5 : 1
            MouseArea{
                id:secMouse
                anchors.fill: parent
                onClicked:rightItemSecondTriggered()
            }
        }
    }
}
