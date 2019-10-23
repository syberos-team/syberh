import QtQuick 2.2

Item {
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    height: 87

    function triangleMarginMenuLeftValue(value){
        bottomTriangle.x = menuRect.x + value
    }

    BorderImage{
        id: menuRect
        source: "./pics/menuBg.sci"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 72
    }
    Image{
        id: bottomTriangle
        anchors.top: menuRect.bottom
        anchors.topMargin: -12
        source: "./pics/triangle_b.png"
        sourceSize: Qt.size(45,28)
    }

    smooth: true
    visible: false
}
