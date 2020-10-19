/*!
 * Author: Mengcong
 * Date: 2013.11.22
 * Details: Controls of player.
 */

import QtQuick 2.0
import QtMultimedia 5.0
import "../../js/config.js" as Config
import com.syberos.basewidgets 2.0

Item {
    id: playerControls

    property MediaPlayer qmlPlayer
    property bool isPortrait: true
    property int currentMediaState: -1
    property int currentMediaStatus: -1
    property bool delayVisible: false
    property alias progressBarVisible: progressBar.progressBarVisible
    property alias ballVisible: progressBar.ballVisible

    signal sigprevious()
    signal signext()
    signal sigplay()
    signal interacted()

    signal sigseek(double position)
    signal sigmove(double position)

    Component.onCompleted: {
        progressBarVisible = playerControls.visible;
        ballVisible = playerControls.visible;
    }
    onVisibleChanged: {
        console.log("playerControls visible changed: ", visible);
    }

    function formatTime(t) {
        t = t / 1000;
        var secs = Math.floor(t % 60);
        t = t / 60;
        var mins = Math.floor(t % 60);
        t = t / 60;
        var hours = Math.floor(t);
        if (secs < 10) secs = "0" + secs;
        if (mins < 10) mins = "0" + mins;
        if (hours < 10) hours = "0" + hours;

        return hours + ":" + mins + ":" + secs;
    }

    function moveProgessBar(seekTo) {
        console.log("moveProgessBar###", seekTo)
        if(progressBarVisible == true && ballVisible == true)
        {
            if(seekTo === qmlPlayer.duration) {
                progressBar.value = 1;
                animateValue.stop();
                progressBar.value = 0;
                return;
            }

//            if(currentMediaState === MediaPlayer.PlayingState) {
//                animateValue.stop();
//                animateValue.from = seekTo / qmlPlayer.duration <= 0 ? 0 : seekTo / qmlPlayer.duration;
//                animateValue.duration = qmlPlayer.duration - seekTo;
//                animateValue.start();
//            } else {
                delayVisible = true;
                progressBar.value = seekTo / qmlPlayer.duration <= 0 ? 0 : seekTo / qmlPlayer.duration;
//            }
        }
    }

    Rectangle{
        anchors.fill: parent
        color: Config.PLAYER_FLOAT_BG
        opacity: 0.9
    }

    ProgressBar {
        id: progressBar
        visible: false

        height: env.dp(50)
        anchors.top: parent.top
        anchors.topMargin: isPortrait ? env.dp(40) : 0// calculate by UI spec
        anchors.left: parent.left
        anchors.leftMargin: isPortrait ? env.dp(40) : env.dp(40)// calculate by UI spec
        anchors.right: parent.right
        anchors.rightMargin: isPortrait ? env.dp(40) : env.dp(40)
        value: 0
        onValueChanged: {
            console.log("position=" + qmlPlayer.position)
            console.log("duration=" + qmlPlayer.duration)
        }

        onSigseek: {
            console.log("onSigseek#######", position)
            interacted()
            playerControls.sigseek(position)
            if(1 != qmlPlayer.playbackState)
                delayVisible = true
        }

        onSigmove: {
            console.log("onSigmove#######", position)
            interacted()
            playerControls.sigmove(position)
        }

        onStopAnimate: {
            animateValue.stop();
        }

        onStartAnimate: {
            console.log("progressBar recv signal StartAnimate , start animateValue#####", position);
            if (qmlPlayer.playbackState == 1) {
                console.log("progressBar recv signal StartAnimate , start animateValue");

                animateValue.from = position
                animateValue.duration = (1.0 - position) * qmlPlayer.duration
                animateValue.start()
            }
        }
    }

    NumberAnimation {
        id: animateValue
        target: progressBar
        properties: "value"
        to: 1
    }

    Timer {
        id:timer
        property int nloop: 0
        interval: 50
        repeat: true
        onTriggered: {
            nloop++;

            console.log("----qmlPlayer.duration---", qmlPlayer.duration)

            if(qmlPlayer.duration !== -1 && qmlPlayer.duration !== 0) {
                console.log("qmlPlayer.duration:" + qmlPlayer.duration);
                animateValue.from = qmlPlayer.position / qmlPlayer.duration <= 0 ? 0 : qmlPlayer.position / qmlPlayer.duration;
                //animateValue.duration = qmlPlayer.duration - cPlayer.position - nloop*timer.interval;
                /* [Bug 35863] (/25*21) 补足环境时间与真实时间差值比例  */
                animateValue.duration = (qmlPlayer.duration - qmlPlayer.position)/25*21;
                timer.stop();
                nloop = 0;
                if(qmlPlayer.playbackState === 1)
                {
                    console.log("timer onTriggered start animateValue");
                    animateValue.start();
                }

            }
        }
    }

    Timer {//timer是为了避免seek操作后，立即取position值还没有更新
        id: delayTimer
        repeat: false
        interval: 50
        onTriggered: {
            // fix bug: if currentMediaState != MediaPlayer.PlayingState, the animateValue moving .
            if(currentMediaState == MediaPlayer.PlayingState) {
                console.log("delayTimer onTriggered start animateValue");
                delayVisible = false;
                animateValue.from = qmlPlayer.position / qmlPlayer.duration <= 0 ? 0 : qmlPlayer.position / qmlPlayer.duration;
                /* [Bug 35863] (/25*21) 补足环境时间与真实时间差值比例  */
                animateValue.duration = (qmlPlayer.duration - qmlPlayer.position)/25*21;
                animateValue.start();
            }
        }
    }

    Text {
        id: currentPosition
        visible: false

        anchors.left: parent.left
        anchors.leftMargin: isPortrait ? env.dp(40) : (40)
        anchors.top: progressBar.bottom
        anchors.topMargin: isPortrait ? env.dp(5) : (2)// calculate by UI spec
        horizontalAlignment: Text.AlignRight
        color: gUiConst.getValue("CT6")
        text: formatTime(qmlPlayer.position)
        font.pixelSize: env.dp(gUiConst.getValue("S6"))
    }

    Text {
        id: duration
        visible: false

        anchors.right: parent.right
        anchors.rightMargin: isPortrait ? env.dp(40) : (40)
        anchors.top: progressBar.bottom
        anchors.topMargin: isPortrait ? env.dp(5) : env.dp(2)
        horizontalAlignment: Text.AlignRight
        color: gUiConst.getValue("CT6")
        text: formatTime(qmlPlayer.duration)
        font.pixelSize: env.dp(gUiConst.getValue("S6"))
    }

    Item {
        id: controlBtn
        width: playerControls.width
        height: env.dp(Config.CONTROL_BUTTON_AREA_HEIGHT)
        anchors.top: progressBar.bottom
        anchors.topMargin: isPortrait ? env.dp(51) : env.dp(22)// calculate by UI spec

        MouseArea{
            anchors.fill: parent
            onClicked: {
                interacted()
            }
        }

        Row {
            id: rowbtn

            spacing: env.dp(Config.CONTROL_BUTTON_SPACING)
            anchors.centerIn: controlBtn

            CButton {
                id: playBtn

                width: env.dp(Config.CONTROL_BUTTON_HEIGHT)
                height: env.dp(Config.CONTROL_BUTTON_HEIGHT)
                backgroundEnabled: false
                iconSource: (qmlPlayer.playbackState == 1 ? "qrc:/img/zanting.png" : "qrc:/img/bofang.png")

                onClicked: {
                    playerControls.sigplay()
                    interacted()
                }
            }

        }
    }

}
