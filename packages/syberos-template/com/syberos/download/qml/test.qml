import QtQuick 2.0

Rectangle {
    width:parent.width
    height: 500
    color: "red"
    property string strText:"static qml"
    Text{
        text :strText
        anchors.verticalCenter: parent.verticalCenter
    }

}
