import QtQuick 2.0

Rectangle {
    id: navigationBar
    color: "#efefef"
    height: 38
    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
    }

    Row {
        height: parent.height - 6
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 3
        }
        spacing: 3
        id: controlsRow
        Rectangle {
            id: backButton
            height: parent.height
            width: height
            color: "#efefef"
            radius: 6

            property alias enabled: webView.canGoBack

            Image {
                anchors.centerIn: parent
                source: "../icons/previous.png"
            }

            Rectangle {
                anchors.fill: parent
                color: parent.color
                radius: parent.radius
                opacity: 0.8
                visible: !parent.enabled
            }

            MouseArea {
                anchors.fill: parent
                onPressed: { if (parent.enabled) parent.color = "#cfcfcf" }
                onReleased: { parent.color = "#efefef" }
                onClicked: {
                    if (parent.enabled) {
                        console.log("MiniBrowser: Going backward in session history.")
                        webView.goBack()
                        webView.forceActiveFocus()
                    }
                }
            }
        }

        Rectangle {
            id: reloadButton
            height: parent.height
            width: height
            color: "#efefef"
            radius: 6
            Image {
                anchors.centerIn: parent
                source: webView.loading ? "../icons/stop.png" : "../icons/refresh.png"
            }

            MouseArea {
                anchors.fill: parent
                onPressed: { parent.color = "#cfcfcf" }
                onReleased: { parent.color = "#efefef" }
                onClicked: {
                    if (webView.loading) {
                        webView.stop()
                    } else {
                        reload()
                    }
                }
            }
        }

        Rectangle {
            id: findButton
            height: parent.height
            width: height
            color: "#efefef"
            radius: 6

            Image {
                anchors.centerIn: parent
                opacity: 0.6
                source: "../icons/find.png"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    findBar.toggle()
                }
            }
        }

    }
}
