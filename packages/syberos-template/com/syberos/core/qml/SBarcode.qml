import QtQuick 2.0
import QtMultimedia 5.2
import com.syberos.basewidgets 2.0
import com.syberos.decodeWorkSpace 1.0


BarcodeScan{
    id: barCodeScanPage

    property var parentPage
    property string strDecodeContent: ""
    property bool pageWillPop : false
    /**
     *解码完成信号
     * @param 解析数据
     */
    signal decodeFinished(string decodeContent)

    signal back(string content)

    Connections {
        target: gWindow
        onActiveChanged: {
            console.log("onActiveChanged gWindow.active ", gWindow.active)
            if (gWindow.active) {
                QtCameraScan.startCameraAndSetZoom();
            } else{
                QtCameraScan.stopCamera();
            }
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Back) {
            if(QtCameraScan.status.toString() == "8"){
                barCodeScanPage.popAndClearStatus();
            }
        }
    }

    function popAndClearStatus(){
        QtCameraScan.stopCamera();
        scanLineRunAnm.stop();
        searchLockTimer.stop();
        startCameraTm.stop();
        back(barCodeScanPage.strDecodeContent);
    }

    contentAreaItem:Rectangle {
        anchors.fill: parent
        BarcodeTitlebar{
            id: pageHead
            onLeftItemTriggered:  {
                popAndClearStatus()
            }
            titleText:"条码扫描"
        }
        Timer{
            id:searchLockTimer
            interval: 2000
            running: false
            repeat: true
            triggeredOnStart:true
            onTriggered: {
                console.log("worksp.camera   status is ", QtCameraScan.status)
                if(QtCameraScan.status.toString() == "8"){
                    console.log("huanlele  9999999999999999999999999999999")
                    QtCameraScan.searchAndLock();
                }
            }
        }

        DecodeWorkSpace{
            id:worksp
            onDecodeFinished: {
                console.log("33333imagepath is ", decodeImagePath,
                            "content is " , decodeContent, "  success  ", success, "  parentPage ", parentPage);
                info.text=
//                        "imagepath is "+ decodeImagePath +
//                        "content is " +
                        decodeContent ;
//                        +"  success  "+ success;
                barCodeScanPage.strDecodeContent = decodeContent.toLowerCase();
                barCodeScanPage.popAndClearStatus();
            }
            onChangedCameraStatus:{
                console.log("huanlilele  camere status is " , status);
                if(QtCameraScan.status.toString() == "8"){
                    barCodeScanPage.enabled = true;
                    console.log("searchLockTimer.start()  scanLineRunAnm.start()")
                    searchLockTimer.start();
                    scanLineRunAnm.start();
                }else {
                    //barCodeScanPage.enabled = false;
                }
            }
        }
        VideoOutput {
            id:videopt
            anchors.top: parent.top
            width: parent.width
            anchors.bottom: parent.bottom
            orientation:-90
            source: QtCameraScan
            fillMode:VideoOutput.Stretch
            focus : visible // to receive focus and capture key events when visible
            onHeightChanged: {
                console.log("videoOutput height is  ", height)
            }
            onWidthChanged: {
                console.log("videoOutput width is  ", width)
            }
        }

        Rectangle{
            id:topRect
            color:"black"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: centerRect.top
            opacity: 0.5
        }
        Rectangle{
            id:btmRect
            color:"black"
            anchors.top: centerRect.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            opacity: 0.5
            Text {
                id: tip
                anchors.top: parent.top
                anchors.topMargin: 40
                anchors.horizontalCenter: parent.horizontalCenter
                color:"#ffffff"
                //font.pixelSize: UI.FONT_SIZE_18
                text: os.i18n.ctr(qsTr("Show bar code in the box, can automatically scan"))
            }
        }
        Rectangle{
            id:leftRect
            color:"black"
            anchors.top: topRect.bottom
            anchors.left: parent.left
            anchors.right: centerRect.left
            anchors.bottom: btmRect.top
            opacity: 0.5
        }
        Rectangle{
            id:rightRect
            color:"black"
            anchors.top: topRect.bottom
            anchors.left: centerRect.right
            anchors.right: parent.right
            anchors.bottom: btmRect.top
            opacity: 0.5
        }

        Item{
            id:centerRect
            width: 300
            height: 300
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            opacity: 0.5
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(QtCameraScan.status == 8){
                        console.log("huanlele  3333333333333333333")
                        QtCameraScan.searchAndLock();
                    }
                }
            }
            Image{
                id:scaLine
                source: "qrc:/com/syberos/core/res/SAOMIAO_56.png"
                width: parent.width
                height: sourceSize.height
                y:0
                x:0
                NumberAnimation on y {
                    id: scanLineRunAnm
                    running: false
                    from: 0; to: centerRect.height
                    loops:Animation.Infinite
                    duration: 4000
                }
            }

        }

        Rectangle{
            anchors.top: centerRect.top
            anchors.left: centerRect.left
            height: 40
            color: "#00ff36"
            width: 4
        }
        Rectangle{
            anchors.bottom: centerRect.bottom
            anchors.left: centerRect.left
            height: 40
            color: "#00ff36"
            width: 4
        }
        Rectangle{
            anchors.top: centerRect.top
            anchors.right: centerRect.right
            height: 40
            color: "#00ff36"
            width: 4
        }
        Rectangle{
            anchors.bottom: centerRect.bottom
            anchors.right: centerRect.right
            height: 40
            color: "#00ff36"
            width: 4
        }
        Rectangle{
            anchors.left: centerRect.left
            anchors.top: centerRect.top
            width: 40
            color: "#00ff36"
            height: 4
        }
        Rectangle{
            anchors.right: centerRect.right
            anchors.top: centerRect.top
            width: 40
            color: "#00ff36"
            height: 4
        }
        Rectangle{
            anchors.left: centerRect.left
            anchors.bottom: centerRect.bottom
            width: 40
            color: "#00ff36"
            height: 4
        }
        Rectangle{
            anchors.right: centerRect.right
            anchors.bottom: centerRect.bottom
            width: 40
            color: "#00ff36"
            height: 4
        }

        Rectangle {
            opacity: 0.5
            width:  parent.width
            height: 90
             id: info_rec
            anchors.top: centerRect.bottom
            anchors.topMargin: 100



            Text {
                  id: info
                anchors.centerIn: parent
                text: ""
                color:"#ffffff"
                //font.pixelSize: UI.FONT_SIZE_18

            }
        }
        Rectangle {
            opacity: 0.5
            width:  parent.width
            height: 160
            anchors.top: info_rec.bottom


        CButton{
            text:"继续扫码"
            width: 300
            height: 120
            anchors.centerIn: parent
            anchors.topMargin: 100
            z:100
            onClicked: {
                //gToast.requestToast("请将摄像头对准二维码或条形码进行扫描")
                info.text="";
                QtCameraScan.startCameraAndSetZoom();
            }

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
            QtCameraScan.startCameraAndSetZoom();
        }
    }

    onStatusChanged:{
        if(status == CPageStatus.Show){
            console.log("BarCodeScan.qml status == CPageStatus.Show  startCameraTimer start")
            startCameraTm.start();
        }else if(status == CPageStatus.WillHide){
            if(barCodeScanPage.parentPage && barCodeScanPage.parentPage.refresh)
                barCodeScanPage.parentPage.refresh = false;
            scanLineRunAnm.stop();
            searchLockTimer.stop();
            startCameraTm.stop();
        }
    }
    Component.onCompleted: {
        gScreenInfo.setStatusBarStyle("transwhite");
        //gScreenInfo.setStatusBar(true)
        console.log("barcode scan  qml  completed--------------")
    }
    Component.onDestruction: {
        gScreenInfo.setStatusBarStyle("transblack");
        if(barCodeScanPage.strDecodeContent != "")
            barCodeScanPage.decodeFinished(barCodeScanPage.strDecodeContent);
        console.log("barcode scan  qml  destruction--------------")
    }

}
