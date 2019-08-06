
import QtQuick 2.5

Image {
    width: 400
    height: 225

    source: "image1.png"

    Image {
        id: overlay

        anchors.fill: parent

        source: "image2.png"

        opacity: 0;
        Behavior on opacity { NumberAnimation { duration: 300 } }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (overlay.opacity === 0)
                overlay.opacity = 1;
            else
                overlay.opacity = 0;
        }
    }
}
// <<M1
