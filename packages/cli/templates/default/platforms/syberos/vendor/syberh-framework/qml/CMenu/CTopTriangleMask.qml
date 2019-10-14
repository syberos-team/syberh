import QtQuick 2.2

Item {
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    height: 87

    property real triangleMarginMenuLeft: 40

    function triangleMarginMenuLeftValue(value){
        topTriangle.x = menuRect.x + value
    }

    Image{
        id: topTriangle
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter //zm added
        source: "./pics/triangle_t.png"
        sourceSize: Qt.size(45,28)
    }
    BorderImage{
        id: menuRect
        source: "./pics/menuBg.sci"
        anchors.top: topTriangle.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 72
    }

    smooth: true
    visible: false
}
