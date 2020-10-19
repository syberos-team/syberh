/*!
 * Author: Mengcong
 * Date: 2013.11.21
 * Details: Playing interface of player.
 */

import QtQuick 2.0
import QtMultimedia 5.5
import com.syberos.basewidgets 2.0
import "../../js/config.js" as Config

CPage {
    id: playingInterface

    property string fileurl
    property bool isSwitchFullScreen : false
    property bool isPlayControlShow: false
    property bool isPortrait: true
    property bool isVolumeKeyPressed: false; ////< 是否手动调节了音量，如果是，则不必定时关闭播放控制界面
    property bool isCalled: false ////< 打电话期间是否播放了视频; true--播放了;false--没有播放
    property bool isHomePressed: false; ////< 播放视频期间是否被Home键中断
    property bool _scaleOk:false
    property bool isSyberosSystem: true;
    property bool neverPlayed: true
    color: "black";

    statusBarHoldEnabled:false
    orientationLock: CPageOrientation.Automatic
    transformOrigin:Item.Center

    //the the number of seconds
    function formatTime(tns) {
        var secs = 0;
        var mins = 0;
        var hours = 0;

        var t = tns/1000;
        secs = Math.floor(t % 60);
        t = t / 60;
        mins = Math.floor(t % 60);
        t = t / 60;
        hours = Math.floor(t);
        if (secs < 10) secs = "0" + secs;
        if (mins < 10) mins = "0" + mins;
        if (hours < 10) hours = "0" + hours;

        return hours + ":" + mins + ":" + secs;
    }

    function pressPrevious() {


    }

    function pressPlay() {
        if(mediaplayer.playbackState == 1){
            mediaplayer.pause()
        } else {
            mediaplayer.play()
        }
    }

    function showAll() {
        console.log("show all")
        animationTopBarShow.restart()
        animationPlayerControlShow.restart()
        timer.restart()
    }

    function showControl() {
        console.log("show control")
        animationTopBarShow.start()
        animationPlayerControlShow.start()
        timer.restart()
    }

    function hideAll() {
        console.log("hide all")
        animationTopBarHide.start()
        animationPlayerControlHide.start()
        timer.stop()
    }

    function changeToLandScape() {
        isPortrait = false
        if(isPlayControlShow) {
            console.log("changeToLandScape: hideAll()")
            hideAll()
        }
    }

    function changeToPortrait() {
        isPortrait = true
        if(isPlayControlShow) {
            console.log("changeToPortrait: hideAll()")
            hideAll()
        }
    }

    function exitAndSave() {
        mediaplayer.stop()
        exit()
    }

    function exit() {
        timer.stop()
        console.log("exit() Back from PlayingInterface page.")
        pageStack.pop()
    }

    property bool useDelayTimer: false

    Timer{
        id: delayTimer
        repeat: false
        interval: 1000
        onTriggered: {
            console.log("delay timer triggered")
//            appWindow.appQuit();
        }
        running: false
    }

    Connections{
        target: gScreenInfo
        onCurrentOrientationChanged:{
            //        Default = 0,
            //        Portrait = 1,
            //        Landscape = 2,
            //        PortraitInverted = 4,
            //        LandscapeInverted = 8,
            //        All = 15
            console.log("current orientation is:" + gScreenInfo.currentOrientation)
            if(gScreenInfo.currentOrientation == CScreenInfo.Portrait || gScreenInfo.currentOrientation == CScreenInfo.PortraitInverted){
                console.log("currentOrientation is screen.Portrait")
                changeToPortrait()
            }else if(gScreenInfo.currentOrientation == CScreenInfo.Landscape || gScreenInfo.currentOrientation == CScreenInfo.LandscapeInverted){
                console.log("currentOrientation is screen.Landscape")
                changeToLandScape()
            }
        }
    }

    Item{
        id:tips

        width: env.dp(170)
        height: env.dp(90)
        anchors.horizontalCenter: playingInterface.horizontalCenter
        anchors.bottomMargin: isPortrait ? env.dp(300) : (200)
        anchors.bottom: playingInterface.bottom
        visible: false
        z: 100

        property string content: ""

        PropertyAnimation{
            id: showTips
            properties: tipsContent.opacity
            from: 0
            to: 0.8
            duration: 1000
            onStarted: {
                tips.visible = true
            }
            onStopped: {
                tipsTimer.restart()
            }
        }

        PropertyAnimation{
            id: hideTips
            properties: tipsContent.opacity
            from: 0.8
            to: 0
            duration: 1000
            onStopped: {
                tips.visible = false
            }
        }

        function showTips(str){
            content = str
            // tips.visible = true
            if(!tips.visible){
                showTips.start()
            }else{
                tipsTimer.restart()
            }
        }

        Timer{
            id:tipsTimer
            interval: 2000
            repeat: false
            onTriggered: {
                //                tips.visible = false
                hideTips.start()
            }
        }

        Rectangle{
            id: tipsContent

            anchors.fill: parent
            color: "#000000"
            opacity: 0.8
            radius: 20

            Text {
                text: tips.content
                anchors.centerIn: parent
                color: "#FFFFFF"
                font.pixelSize: env.dp(30)
            }
        }
    }

    Component.onCompleted: {
        console.log("PlayingInterface:Component.onCompleted")
        console.log("height=" +  height)
        playingInterface.statusBarHoldEnabled = false
        gScreenInfo.setStatusBar(false)
    }


    MediaPlayer {
         id: mediaplayer
         autoPlay: true
         source: fileurl
         onStopped: {
             if (mediaplayer.position === mediaplayer.duration) {
                 console.log("mediaplayer onStopped###", mediaplayer.position, mediaplayer.duration)
                 console.log("mediaplayer onStopped###", mediaplayer.position/mediaplayer.duration)
                 mediaplayer.play()
                 mediaplayer.pause()
             }
         }
    }


    QmlVideoOutput {
        id: videooutput

        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        color: gUiConst.getValue("color05")
        sourceMedia: mediaplayer
    }


    MouseArea {
        id: marea
        property int originalX;
        property int originalY;
        property int distanceX;
        property int distanceY;
        property int oriVol;

        anchors.fill: parent

        onPressed: {
            console.log("MouseArea onPressed x = " + mouseX + "  y = " + mouseY )
            originalX = mouseX;
            originalY = mouseY;
            if(!isPlayControlShow) {
                showAll()
            }
        }

        onReleased: {
            if (isPlayControlShow) {
                hideAll()
            }
        }


    }


//    VideoOutput {
//       id: videooutput
//       anchors.fill: playingInterface
//       source: mediaplayer
//    }

    CTitleBar {
        id: playingTopBar

        height: env.dp(89)
        anchors.top: parent.top
        anchors.topMargin:env.dp(-89)
        anchors.left: parent.left
        leftItemEnabled: true
        titleItemEnabled: true
        rightItemEnabled: false
        titleText: fileurl.split('/')[fileurl.split('/').length-1]
        titleTextColor: gUiConst.getValue("CT3")
        titlePixelSize: env.dp(gUiConst.getValue("S1"))
        backgroundEnabled: true

        onLeftItemTriggered: {
            console.log("onLeftItemTriggered")
            exitAndSave()
        }

        backgroundComponent: Component{
            Rectangle{
                anchors.fill: parent
                color: "#232323"
                opacity: 0.9
            }
        }

        PropertyAnimation {
            id: animationTopBarShow

            target: playingTopBar
            properties: "anchors.topMargin"
            from: env.dp(-89)
            to: 0
            duration: 200
        }

        PropertyAnimation {
            id: animationTopBarHide

            target: playingTopBar
            properties: "anchors.topMargin"
            from: 0
            to: env.dp(-89)
            duration: 200
        }
    }

    Timer {
        id: timer

        interval: 5000
        onTriggered: {
            console.log("Timer. onTriggered.")
            timer.stop()
            animationPlayerControlHide.start()
            animationTopBarHide.start()
        }
    }

    Timer{
        id:timer_hideexpandBtn

        interval: 5000
        onTriggered: {
            portExpandBtn.visible = false
        }
    }

    //For landscape end

    PlayerControls {
        id: playerControl
        visible: false
        qmlPlayer: mediaplayer
        width: parent.width
        height: isPortrait ? env.dp(Config.CONTROL_HEIGHT_PORT) : env.dp(Config.CONTROL_HEIGHT)
        anchors.left:  parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: isPortrait ? env.dp(-Config.CONTROL_HEIGHT_PORT) : env.dp(-Config.CONTROL_HEIGHT)

        isPortrait: playingInterface.isPortrait
        onVisibleChanged: {
            console.log("y:-------------", y);
        }



        PropertyAnimation {
            id: animationPlayerControlShow

            target:playerControl
            properties: "anchors.bottomMargin"
            from: isPortrait ? env.dp(-Config.CONTROL_HEIGHT_PORT) : env.dp(-Config.CONTROL_HEIGHT)
            to: 0
            duration: 200
            onStopped: {
                isPlayControlShow = true
                playerControl.visible = true;
                playerControl.progressBarVisible = true;
                playerControl.ballVisible = true;
            }
        }

        PropertyAnimation {
            id: animationPlayerControlHide

            target:playerControl
            properties: "anchors.bottomMargin"
            from: 0
            to: isPortrait ? env.dp(-Config.CONTROL_HEIGHT_PORT) : env.dp(-Config.CONTROL_HEIGHT)
            duration: 200
            onStopped: {
                isPlayControlShow = false
                playerControl.visible = false;
                playerControl.progressBarVisible = false;
                playerControl.ballVisible = false;
            }
        }

        onInteracted: {
            timer.restart()
        }


        onSigplay: {
            // 2 => Loading
            if(mediaplayer.status !== 2){
                pressPlay()
            }
        }


        onSigseek: {
            console.log("onSigseek--position: ", position);
            var millisecs = mediaplayer.duration * position;
            mediaplayer.position = millisecs;
            mediaplayer.seek(millisecs)
            console.log("onSigseek--position: ", mediaplayer.position);
            if(position == 1) {
                tips.showTips(formatTime(0));
            } else {
                tips.showTips(formatTime(millisecs));
            }
        }

        onSigmove: {
            var millisecs = qmlPlayer.duration * position;
            tips.showTips(formatTime(millisecs));
        }
    }

    onStatusChanged: {
//        if (status === CPageStatus.Show) {
//            console.log("PlayingInterface: pagestauts is Show");
//            console.log("PlayingInterface: fileurl: " + fileurl);
//            if(cPlayer.havingCall() === true)
//            {
//                //打电话期间，禁止播放视频
//                console.log("Audio device has been occupied, Unable to play");
//                tips.showTips(os.i18n.ctr(qsTr("Audio device has been occupied, Unable to play")));
//                cPlayer.setMediaSource("");
//                playingTopBar.titleText = cPlayer.getFileName(fileurl);
//                isCalled = true;
//                neverPlayed = true
//            }
//            else
//            {
//                cPlayer.setMediaSource(fileurl);
//                neverPlayed = false
//            }
//            if(gScreenInfo.currentOrientation == CScreenInfo.Portrait || gScreenInfo.currentOrientation == CScreenInfo.PortraitInverted){
//                console.log("currentOrientation is screen.Portrait")
//                isPortrait = true
//            }else if(gScreenInfo.currentOrientation == CScreenInfo.Landscape || gScreenInfo.currentOrientation == CScreenInfo.LandscapeInverted){
//                console.log("currentOrientation is screen.Landscape")
//                isPortrait = false
//            }
//        }else if(status === CPageStatus.WillShow){
//            console.log("PlayingInterface: pagestauts is WillShow");
////            windowDealer.setStatusBarVisible(false);
//            gScreenInfo.setWindowProperty("STATUSBAR_VISIBLE", false);
//            console.log("currentOrientation is:" + gScreenInfo.currentOrientation)
//        }else if(status === CPageStatus.WillHide){
//            console.log("PlayingInterface: pagestauts is WillHide");
//        }else if (status === CPageStatus.Hide) {
//            console.log("PlayingInterface: pagestauts is Hide, isPlaying:", cPlayer.isPlaying);
//            if(cPlayer.isPlaying === 1){
//                cPlayer.stop()
//                timer.stop()
//            }
//        }
    }
    onActiveChanged: {
        if(!active)
        {
            console.log("onActiveChanged: false");
//            if(cPlayer.isPlaying === 1){
//                cPlayer.pause()
//                timer.stop()
//            }
//            console.log("onActiveChanged curMode:",appWindow.curMode)
//            if(appWindow.curMode === 1)
//           {
//                isHomePressed = true; //只有在主界面启动播放器，才需要设置home键状态。
//            }
//            if(appWindow.curMode === 3)
//            {
//                //如果是第三方软件打开的播放器，当用户按Home键后，则允许第三方软件启动播放器。
//                appWindow.isThirdPartOpenfileed = false;
//            }
//            console.log("onActiveChanged: isThirdPartOpenfileed = ",  appWindow.isThirdPartOpenfileed);
        }
    }


    CIndicator{
        id:indicator
        anchors.centerIn: parent
        visible: false
    }
}
