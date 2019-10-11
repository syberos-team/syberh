import QtQuick 2.2
import "./"

Rectangle {
    id: menuItemBg
    height: SingletonTool.menuItemHeight
    gradient: pressing ? pressColor : normalColor

    property int textVerticalCenterOffset: 13
    property alias text: txtArea.text
    property bool pressing: false
    property Gradient pressColor: Gradient {
        GradientStop { position: 0.0; color: "#333333" }
    }
    property Gradient normalColor: Gradient {
        GradientStop { position: 0.0; color: "#575757" }
        GradientStop { position: 0.7; color: "#222222" }
    }

    Text {
        id: txtArea
        anchors.centerIn: parent
        anchors.verticalCenterOffset: textVerticalCenterOffset
        font.pixelSize: 24
        color: "#FFFFFF"
        onTextChanged: {
            menuItemBg.width = Qt.binding(function() {return txtArea.paintedWidth + 42})
        }
    }
}
