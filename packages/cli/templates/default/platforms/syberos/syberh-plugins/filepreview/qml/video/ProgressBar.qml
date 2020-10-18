/*!
 * Author: Mengcong
 * Date: 2013.11.22
 * Details: Progress bar.
 */

import QtQuick 2.0
import QtQuick.Controls.Styles 1.2
import QtQuick.Controls 1.2

import "../../js/config.js" as Config

Item {
    id: progressBar

    property double value: 0.0
    property alias interactive: maProgressBar.enabled
    property alias progressBarVisible: greenRec.visible
    property alias ballVisible: ball.visible
    property int _userX;

    signal stopAnimate()
    signal startAnimate(double position)
    signal sigseek(double position)
    signal sigmove(double position)

    Rectangle {
        width: parent.width
        height: env.dp(20)
        anchors.left: parent.left
        anchors.bottom: whiteRec.top
        color: "#00000000"
    }

    Rectangle {
        id: whiteRec

        width: parent.width
        height: env.dp(Config.CONTROL_PROGRESS_BAR_HEIGHT)
        anchors.verticalCenter: parent.verticalCenter
        color: "white"
        opacity: 0.2
        radius: 8
    }

    ProgressBar {
        id: greenRec;
        visible: true;
        maximumValue: 1;
        minimumValue: 0;
        value: visible ? progressBar.value : 0.0
        width: parent.width;
        height: env.dp(Config.CONTROL_PROGRESS_BAR_HEIGHT);
        anchors.verticalCenter: parent.verticalCenter
        style: ProgressBarStyle {
            background: Rectangle {
                implicitWidth: greenRec.width;
                implicitHeight: greenRec.height;
                border.width: env.dp(1);
                border.color:  greenRec.hovered ? gUiConst.getValue("CA1") : "gray";
                color: "lightgray";
                radius: 8;
            }
            progress: Rectangle {
                color:  gUiConst.getValue("CA1") ;
                radius: 8;
            }
        }
    }


    Rectangle {
        width: parent.width
        height: env.dp(20)
        anchors.left: parent.left
        anchors.top: greenRec.bottom
        color: "#00000000"
    }



    Rectangle {
        id: ball
        visible:  true;
        x:visible ? (maProgressBar.pressed ? _userX - width / 2 : value * parent.width - width / 2) : 0
        anchors.verticalCenter: parent.verticalCenter
        width: env.dp(Config.CONTROL_PROGRESS_CURSOR + 5)
        height: env.dp(Config.CONTROL_PROGRESS_CURSOR + 5)
        radius: width/2;
        color: "white"
        onXChanged: {
//            console.log("ball changed position: ", x);
//            console.log("ball is visible: ", visible);
        }
    }



    MouseArea {
        id: maProgressBar

        anchors.fill: parent
        onPressed: {
            console.log("Press progress bar")
            progressBar.stopAnimate()
            progressBar._userX = Math.min(width, Math.max(0, mouseX));
            var tmpValue = Math.min(width, Math.max(0, mouseX)) / width;
            progressBar.sigmove(tmpValue);
        }

        onPositionChanged: {
            console.log("Position changed")
            if (pressed) {
                console.log("Pressed")
                progressBar._userX = Math.min(width, Math.max(0, mouseX));
                var tmpValue = Math.min(width, Math.max(0, mouseX)) / width;
                value = tmpValue;
                sigmove(tmpValue);
            }
        }

        onReleased: {
            var tmpValue = Math.min(width, Math.max(0, mouseX)) / width;
            value = tmpValue
            console.log("Release progress bar")
            progressBar.sigseek(tmpValue);
            progressBar.startAnimate(tmpValue);
        }
    }

}
