pragma Singleton
import QtQuick 2.0
import "./CMenu"

Item {
    id: selectContainer
    property rect selectRect
    function setCursor(wv, show, rect) {
        if(selectContainer.parent != wv)
            selectContainer.parent = wv;
        if( !cusror1.pressed && !cusror2.pressed){
            visible = show;
            if(show){
                startCursor.cx = rect.x
                startCursor.cy = rect.y

                endCursor.cx = rect.x + rect.width
                endCursor.cy = rect.y + rect.height
                console.log("setCursor=======" , startCursor.x, startCursor.y, endCursor.x, endCursor.y);
            }
        }

        selectRect = rect
        copyPasetMenu.visible = true
        copyPasetMenu.x = endCursor.x + endCursor.width/2 - copyPasetMenu.width/2
        copyPasetMenu.menuOffsetY = endCursor.y + endCursor.height  + selectContainer.parent.contentY
    }

    function selectPress(vm, start)
    {
        vm.selectPress(start)
    }

    Image{
        id: startCursor
        width: 33
        height: 60
        opacity:!cusror1.pressed ? 1 : 0
        source: "qrc:/res/startHandleUp.png"

        property int cx: 0
        property int cy: 0
        x: -selectContainer.parent.contentX + cx -width
        y: -selectContainer.parent.contentY + cy + height

        onYChanged: {
            console.log("startCursor.y=============", y ,selectContainer.parent.contentY, cy)
        }

        onStatusChanged: if (image.status === Image.Ready) console.log("--------------------------------startHandleUp-----------------------")

        MouseArea{
            id: cusror1
            property int pressx: 0
            property int pressy: 0
            onPositionChanged: {
                if(cusror1.pressed || cusror2.pressed) {
                    console.log("cusror1.onPositionChanged", mouse.x, mouse.y)
                    if(selectContainer.parent && selectContainer.parent.selectPosition)
                    {
                        var oldRectHeight = selectRect.height
                        var oldRectWidth = selectRect.width
                        selectContainer.parent.selectPosition(mouse.x - pressx, mouse.y- pressy)
                        if(selectRect.y > endCursor.cy -oldRectHeight || (selectRect.y === endCursor.cy-oldRectHeight && selectRect.x > endCursor.cx -oldRectWidth))
                        {
                            moveCursor.posChanged = true
                        }
                        else
                        {
                            moveCursor.posChanged = false
                        }
                    }
                }
            }
            anchors{ fill: parent; margins: -10 }
            onPressed: {
                selectPress(selectContainer.parent, true);
                pressx = mouse.x;
                pressy = mouse.y;
                //                parent = selectContainer;
                console.log("cusror1.onPressed", mouse.x, mouse.y)
                //                mouse.accepted = false
            }

            onReleased: {
                moveCursor.posChanged = false
                setCursor(selectContainer.parent, true, selectRect);
                copyPasetMenu.visible = true
                copyPasetMenu.x = startCursor.x + startCursor.width/2 - copyPasetMenu.width/2
                if(copyPasetMenu.x < 0)
                {
                    copyPasetMenu.x = 0
                }
                else if(copyPasetMenu.x > gAppUtils.pageStackWindow.width - copyPasetMenu.width)
                {
                    copyPasetMenu.x = copyPasetMenu.x = gAppUtils.pageStackWindow.width - copyPasetMenu.width
                }

                copyPasetMenu.menuOffsetY = startCursor.y + startCursor.height  + selectContainer.parent.contentY
            }
        }

    }

    Image{
        id: endCursor
        width: 33
        height: 60
        opacity: !cusror2.pressed ? 1 : 0
        source: "qrc:/res/endHandle.png"

        property int cx: 0
        property int cy: 0
        x: -selectContainer.parent.contentX + cx
        y: -selectContainer.parent.contentY + cy + height
        onStatusChanged: if (image.status === Image.Ready) console.log("--------------------------------endHandle-----------------------")

        MouseArea{
            id: cusror2
            property int pressx: 0
            property int pressy: 0
            onPositionChanged: {
                if(cusror1.pressed || cusror2.pressed) {
                    console.log("cusror1.onPositionChanged", mouse.x, mouse.y)
                    if(selectContainer.parent && selectContainer.parent.selectPosition){
                        selectContainer.parent.selectPosition(mouse.x - pressx, mouse.y- pressy)
                        if(selectRect.y < startCursor.cy || (selectRect.y === startCursor.cy && selectRect.x < startCursor.cx))
                        {
                            moveCursor.posChanged = true
                        }
                        else
                        {
                            moveCursor.posChanged = false
                        }
                    }
                }
            }
            anchors{ fill: parent; margins: -10 }
            onPressed: {
                selectPress(selectContainer.parent, false);
                pressx = mouse.x;
                pressy = mouse.y;
                //                parent = selectContainer;
                console.log("cusror2.onPressed", mouse.x, mouse.y)
                //                mouse.accepted = false
            }

            onReleased: {
                moveCursor.posChanged = false
                setCursor(selectContainer.parent, true, selectRect);
                copyPasetMenu.visible = true
                copyPasetMenu.x = endCursor.x + endCursor.width/2 - copyPasetMenu.width/2
                if(copyPasetMenu.x > gAppUtils.pageStackWindow.width - copyPasetMenu.width)
                {
                    copyPasetMenu.x = gAppUtils.pageStackWindow.width - copyPasetMenu.width
                }
                else if (copyPasetMenu.x < 0)
                {
                    copyPasetMenu.x = 0
                }

                copyPasetMenu.menuOffsetY = endCursor.y + endCursor.height + selectContainer.parent.contentY
            }
        }
    }

    Image{
        id: moveCursor
        width: 33
        height: 60

        property bool posChanged: false

        x: -selectContainer.parent.contentX
           + (cusror1.pressed ?
                  (posChanged?selectRect.x + selectRect.width -width :selectRect.x-width)
                : (posChanged? selectRect.x :selectRect.x + selectRect.width))
        y: -selectContainer.parent.contentY + height
           + (cusror1.pressed ?
                  (posChanged ? selectRect.y + selectRect.height : selectRect.y)
                : (posChanged ? selectRect.y : selectRect.y + selectRect.height))
        visible: cusror1.pressed || cusror2.pressed
        source: cusror1.pressed?"qrc:/res/startHandleUp.png":"qrc:/res/endHandle.png"

        onStatusChanged: if (image.status === Image.Ready) console.log("--------------------------------startHandleUp/endHandle-----------------------")
    }

    CContentsMenu{
        id: copyPasetMenu
        visible: false

        width: leftWidth + centerWidth

        leftText: os.i18n.ctr(qsTr("Copy"))
        centerText: os.i18n.ctr(qsTr("Paste"))

        property int menuOffsetY: 0

        x: 0
        y: -selectContainer.parent.contentY + menuOffsetY

        onVisibleChanged:
        {
            if(visible)
            {
                showThree()                
            }
        }

        onTriggerLeft: {
            selectContainer.parent.textCmd("copy")
            visible = false
        }

        onTriggerCenter: {
            selectContainer.parent.textCmd("paste")
            visible = false
        }

        Component.onCompleted: {
            moveMenu(leftWidth+x,100)
        }
    }
}


