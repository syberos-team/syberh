import QtQuick 2.0
import QtGraphicalEffects 1.0
import "./"
import QtQuick.Window 2.1

Item {
    id: content
    height: SingletonTool.menuFixedHeight

    property alias leftText: leftArea.text
    property alias centerText: centerArea.text
    property alias rightText: rightArea.text
    property alias leftWidth: leftArea.width
    property alias centerWidth: centerArea.width
    property alias rightWidth: rightArea.width

    signal triggerLeft()
    signal triggerCenter()
    signal triggerRight()

    function moveMenu(x,y){
        var xPos = x - content.width/2

        if(SingletonTool.menuArrowTowardUp){
            if(!maskTop){
                var component = Qt.createComponent("CTopTriangleMask.qml");
                if (component.status === Component.Ready) {
                    maskTop = component.createObject(content);
                }
            }
            opacityMask.maskSource = maskTop
            fullBgArea.textOffset = 12
            // set mouse visible area
            fullMouseItem.y = fullBgArea.y + SingletonTool.triangleHeight
            fullBgArea.divYPos = 2
        }else{
            if(!maskBottom){
                var component1 = Qt.createComponent("CBottomTriangleMask.qml");
                if (component1.status === Component.Ready) {
                    maskBottom = component1.createObject(content);
                }
            }
            opacityMask.maskSource = maskBottom
            fullBgArea.textOffset = -13
            fullMouseItem.y = fullBgArea.y
            fullBgArea.divYPos = 0
        }

        if( xPos <= 2 ){
            xPos = 2
        }else if( xPos >= gScreenInfo.desktopAvailableWidth - content.width - 2 ){
            xPos = gScreenInfo.desktopAvailableWidth - content.width - 2
        }

        var v = x - SingletonTool.triangleWidth/2 - xPos
        var margin = SingletonTool.bound( SingletonTool.triangleMargin, v, (content.width - SingletonTool.triangleWidth - SingletonTool.triangleMargin))

//zm
//        if(maskTop)
//            maskTop.triangleMarginMenuLeftValue(margin)
        if(maskBottom)
            maskBottom.triangleMarginMenuLeftValue(margin)
//zm
//        content.x = x
//        content.y = y
    }

    function showOne(){
        leftMouse.visible = true
        centerMouse.visible = false
        rightMouse.visible = false

        leftArea.visible = true
        divLeft.visible = false
        centerArea.visible = false
        divRight.visible = false
        rightArea.visible = false
    }

    function showTwo(){
        leftMouse.visible = true
        centerMouse.visible = false
        rightMouse.visible = true

        leftArea.visible = true
        divLeft.visible = true
        centerArea.visible = false
        divRight.visible = false
        rightArea.visible = true
    }

    function showThree(){
        leftMouse.visible = true
        centerMouse.visible = true
        rightMouse.visible = true

        leftArea.visible = true
        divLeft.visible = true
        centerArea.visible = true
        divRight.visible = true
        rightArea.visible = true
    }

    property CTopTriangleMask maskTop
    property CBottomTriangleMask maskBottom

    Item {
        id: fullMouseItem
        width: parent.width
        height: SingletonTool.menuItemHeight


        MouseArea{
            id: leftMouse
            width: leftArea.width
            height: SingletonTool.menuItemHeight + 30
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            onReleased: {
                if(containsMouse)
                {
                    content.triggerLeft()
                }
                 mouse.accepted = true
            }
        }
        MouseArea{
            id: centerMouse
            width: centerArea.width
            height: SingletonTool.menuItemHeight + 30
            anchors.left: leftMouse.right
            anchors.right: rightMouse.left
            anchors.verticalCenter: parent.verticalCenter
            onReleased:{
                if(containsMouse)
                {
                    content.triggerCenter()
                }
                mouse.accepted = true
            }
        }
        MouseArea{
            id: rightMouse
            width: rightArea.width
            height: SingletonTool.menuItemHeight + 30
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            onReleased: {
                if(containsMouse)
                {
                    content.triggerRight()
                }
                mouse.accepted = true
            }
        }
    }

    Rectangle {
        id: fullBgArea
        anchors.fill: parent
        smooth: true
        visible: false

        property int textOffset: -13
        property int divYPos: 0

        Row{
            id: itemRow
            width: parent.width
            spacing: 0
            CMenuItem {
                id: leftArea
                height: parent.height
                textVerticalCenterOffset: fullBgArea.textOffset
                pressing: leftMouse.pressed
            }
            CMenuDiv{ id:divLeft; y: fullBgArea.divYPos }
            CMenuItem {
                id: centerArea
                height: parent.height
                textVerticalCenterOffset: fullBgArea.textOffset
                pressing: centerMouse.pressed
            }
            CMenuDiv{ id:divRight; y: fullBgArea.divYPos }
            CMenuItem {
                id: rightArea
                height: parent.height
                textVerticalCenterOffset: fullBgArea.textOffset
                pressing: rightMouse.pressed
            }
        }
    }

    OpacityMask {
        id: opacityMask
        anchors.fill: fullBgArea
        source: fullBgArea
        maskSource: maskBottom
    }
}
