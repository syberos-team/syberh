/*!
* \file BarCodeScan.qml
* \brief 一二维码扫描页面
*
*此界面一二维码扫描页面，调用相机取帧，并对取到的帧进行解析，如果解析成功，返回解析数据
*
*\author 桓乐乐 huanlele@syberos.com
*\version 1.0
*\date 2015/9/7
*/
import QtQuick 2.1
import QtMultimedia 5.0
import com.syberos.basewidgets 2.0
import com.syberos.decodeWorkSpace 1.0
import QtGraphicalEffects 1.0
/*!
  \class BarCodeScan
  \inModule 公共控件
  \brief 一二维码扫描页面
  \ingroup common
  此界面一二维码扫描页面，调用相机取帧，并对取到的帧进行解析，如果解析成功，返回解析数据

*/
CPage {
    id: barCodeScanPage
    focus: true
    property alias scanTitle:titleBar.titleText

    QtObject{
        id:internalDataObject
        property string strDecodeContent: ""
        property bool isDecodeSuccess:false
    }


    color:"#000000"
    orientationPolicy: CPageOrientation.LockPortrait
    enabled: CPageStatus.Show


    onStatusChanged:{
        if(status == CPageStatus.Show){
            console.log("BarCodeScan.qml status == CPageStatus.Show  startCameraTimer start")
            startCameraTm.start();
            gScreenInfo.setStatusBarStyle("transwhite");
        }else if(status == CPageStatus.WillHide){
            scanLineRunAnm.stop();
            searchLockTimer.stop();
            startCameraTm.stop();
        }
//        else if(status == CPageStatus.Hide)
//        {
//            console.log("---------------status == CPageStatus.Hide")
//            if(internalDataObject.isDecodeSuccess)
//            {
//                console.log("---------------status == CPageStatus.Hide 2222")
//                decodeFinished(internalDataObject.strDecodeContent)
//            }
//        }
    }

    /**
     *解码完成信号
     * @param 解析数据
     */
    signal decodeFinished(string decodeContent)

    signal cancel()
//    Connections {
//        target: gWindow
//        onActiveChanged: {
//            console.log("onActiveChanged gWindow.active ", gWindow.active)
//            if (gWindow.active) {
//                QtCamera.startCameraAndSetZoom();
//            } else{
//                QtCamera.stopCamera();
//            }
//        }
//    }

    Keys.onReleased: {
        if (event.key === Qt.Key_Back) {
            event.accepted = true;
            popAndClearStatus()
            cancel()
        }
    }

    function popAndClearStatus(){
        QtCamera.stopCamera();
        scanLineRunAnm.stop();
        searchLockTimer.stop();
        startCameraTm.stop();
//        pageStack.pop()
    }



    Timer{
        id:searchLockTimer
        interval: 2000
        running: false
        repeat: true
        triggeredOnStart:true
        onTriggered: {
            console.log("worksp.camera   status is ", QtCamera.status)
            if(QtCamera.status.toString() == "8"){
                console.log("huanlele  9999999999999999999999999999999")
                QtCamera.searchAndLock();
            }
        }
    }
    Timer{
        id:startCameraTm
        interval: 300
        running: false
        repeat: false
        onTriggered: {
            console.log("QtCamera.startCameraAndSetZoom();")
            QtCamera.startCameraAndSetZoom();
        }
    }



    DecodeWorkSpace{
        id:worksp
        onDecodeFinished: {
            console.log("33333imagepath is ", decodeImagePath,
                        "content is " , decodeContent, "  success  ", success);
            //info.text=decodeContent ;
            internalDataObject.strDecodeContent = decodeContent //.toLowerCase();
            internalDataObject.isDecodeSuccess = true
            barCodeScanPage.popAndClearStatus();
            barCodeScanPage.decodeFinished(decodeContent)
        }
        onChangedCameraStatus:{
            console.log("huanlilele  camere status is " , status);
            if(QtCamera.status.toString() == "8"){
                barCodeScanPage.enabled = true;
                console.log("searchLockTimer.start()  scanLineRunAnm.start()")
                searchLockTimer.start();
                scanLineRunAnm.start();
            }else {
                //barCodeScanPage.enabled = false;
            }
        }
    }

    CTitleBar{
        id:titleBar
        anchors.top: parent.top
        anchors.topMargin: env.dp(48)
        leftItemIcon:"qrc:///res/iconBack.png"
        leftItemBackgroundEnabled: false
        leftItemSize: Qt.size(env.dp(20),env.dp(20))

        spacingBetweenLeftBorderAndLeftItem: env.dp(40)

        spacingBetweenLeftItemAndTitleItem: env.dp(18)
        titlePixelSize: env.dp(40)
        titleText: "二维码扫描"
        titleTextColor: "#ffffff"

        onLeftItemChanged: {
            if(leftItem)
            {
                leftItem.spacing = 18
            }
        }
    }
    VideoOutput {
        id:videopt
        anchors.top: titleBar.bottom
        width: parent.width
        anchors.bottom: parent.bottom
        orientation:-90
        source: QtCamera
        fillMode:VideoOutput.Stretch
        focus : visible // to receive focus and capture key events when visible

        Rectangle{
            id:outareaTop
            anchors.top: parent.top
            width:parent.width
            anchors.bottom: scanAreaOut.top
            color:"#3b4050"
            opacity: 0.5
        }
        Rectangle{
            id:outareaRight
            anchors.top: outareaTop.bottom
            anchors.right: parent.right
            anchors.left: scanAreaOut.right
            anchors.bottom: outareaBottom.top
            color:"#3b4050"
            opacity: 0.5
        }
        Rectangle{
            id:outareaBottom
            anchors.top: scanAreaOut.bottom
            width:parent.width
            anchors.bottom: parent.bottom
            color:"#3b4050"
            opacity: 0.5
        }
        Rectangle{
            id:outareaLeft
            anchors.top: outareaTop.bottom
            anchors.right: scanAreaOut.left
            anchors.left: parent.left
            anchors.bottom: outareaBottom.top
            color:"#3b4050"
            opacity: 0.5
        }

        Image {
            id: scanAreaOut
            source: "qrc:///res/scanAreaOut.png"
            width: env.dp(320)
            height: env.dp(320)
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
            Image {
                id: scanAreaCorner
                source: "qrc:///res/scanAreaCorner.png"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }
            Image {
                id: scanLine
                width:parent.width-2
                height: env.dp(9)
                source: "qrc:///res/scanLine.png"
                fillMode: Image.PreserveAspectFit
                //anchors.centerIn: parent
                y:0
                x:0
                NumberAnimation on y {
                    id: scanLineRunAnm
                    running: false
                    from: 0; to: scanAreaOut.height
                    loops:Animation.Infinite
                    duration: 4000
                }
            }


        }


    }


//        Rectangle {
//            opacity: 0.5
//            width:  parent.width
//            height: 160
//            anchors.bottom: parent.bottom
//            Text {
//                id: info
//                anchors.bottom: cancelButton.top
//                text: ""
//                color:"#ffffff"
//                //font.pixelSize: UI.FONT_SIZE_18

//            }

//            CButton{
//                id:cancelButton
//                text:"继续扫码"
//                width: 300
//                height: 120
//                anchors.centerIn: parent
//                anchors.topMargin: 100
//                z:100
//                onClicked: {
//                    //gToast.requestToast("请将摄像头对准二维码或条形码进行扫描")
//                    info.text="";
//                    QtCamera.startCameraAndSetZoom();
//                }

//            }

//        }


    CButton{
        id:cancelButton
        text: "取消"
        textColor: "#ffffff"
        width: env.dp(580)
        height: env.dp(80)
        pixelSize: env.dp(36)
        backgroundComponent: Rectangle{
            radius: env.dp(50)
            color:"#2d56d2"
        }
        anchors.bottom: parent.bottom
        anchors.bottomMargin: env.dp(58)
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            popAndClearStatus()
            barCodeScanPage.cancel()
        }
    }

}
