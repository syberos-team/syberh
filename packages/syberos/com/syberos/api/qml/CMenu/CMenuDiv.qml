import QtQuick 2.2

Item{
    width: 2
    height: 88
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        width: 1
        height: parent.height
        gradient: Gradient{
            GradientStop { position: 0.0; color: "#111111" }
            GradientStop { position: 0.6; color: "#000000" }
            GradientStop { position: 1.0; color: "#000000" }
        }
        //opacity: 0.7
    }
    Rectangle {
        anchors.top: parent.top
        anchors.right: parent.right
        width: 1
        height: parent.height
        gradient: Gradient{
            GradientStop { position: 0.0; color: "#444444" }
            GradientStop { position: 0.6; color: "#222222" }
            GradientStop { position: 0.7; color: "#000000" }
            GradientStop { position: 1.0; color: "#000000" }
        }
        //opacity: 0.7
    }
}
