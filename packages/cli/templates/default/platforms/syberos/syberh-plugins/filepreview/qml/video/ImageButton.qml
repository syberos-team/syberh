/*!
 * Author: Mengcong
 * Date: 2013.11.18
 * Details: Image button tool.
 */

import QtQuick 2.0

Item {
    id: buttonItem
    property string source1: ""
    property string source2: ""
    property string align: "center"

    property alias imageWidth: image.width
    property alias imageHeight: image.height

    signal clicked()

    function setAlign(align){
        if(align === "center"){
            image.anchors.centerIn = buttonItem
        }else if(align === "left"){
            image.anchors.left = buttonItem.left
        }else if(align === "right"){
            image.anchors.right = buttonItem.right
        }else if(align === "top"){
            image.anchors.top = buttonItem.top
        }else if(align === "bottom"){
            image.anchors.bottom = buttonItem.bottom
        }
    }

    Component.onCompleted: {
        setAlign(align)
    }

    MouseArea {
        id: mouseArea

        //for test hot area
//        Rectangle{
//            anchors.fill: parent
//        }

        anchors.fill: parent

        onClicked: {
            parent.clicked()
        }
    }

    Image {
        id: image

        source: source1
        fillMode: Image.PreserveAspectFit

        states: [
            State {
                name: "pressed"
                when: mouseArea.pressed
                PropertyChanges {
                    target: image
                    source: source2
                }
            }
        ]
    }
}
