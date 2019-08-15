import QtQuick 2.0
import QtMultimedia 5.2
import com.syberos.basewidgets 2.0
import com.syberos.decodeWorkSpace 1.0
import "../js/barcode/constants.js" as UI


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
                barCodeScanPage.clearStatusAndBack();
            }
        }
    }

    function clearStatusAndBack(){
        QtCameraScan.stopCamera();
        scanLineRunAnm.stop();
        searchLockTimer.stop();
        startCameraTm.stop();
        barCodeScanPage.back(barCodeScanPage.strDecodeContent);
    }

    contentAreaItem:Rectangle {
        anchors.fill: parent
        BarcodeTitlebar{
            id: pageHead
            onLeftItemTriggered:  {
                clearStatusAndBack()
                pageStack.pop()
            }
            titleText:"扫码"
        }
        Timer{
            id:searchLockTimer
            interval: 1200
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
                barCodeScanPage.strDecodeContent = decodeContent.toLowerCase();
                barCodeScanPage.clearStatusAndBack();
                pageStack.pop();
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
            anchors.top: pageHead.bottom
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
                font.pixelSize: UI.FONT_SIZE_10
                text: os.i18n.ctr(qsTr("放入框内，自动扫描"))
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
            width: 450
            height: 450
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
    }


    Timer{
        id:startCameraTm
        interval: 1000
        running: false
        repeat: false
        onTriggered: {
            QtCameraScan.startCameraAndSetZoom();
        }
    }

    onStatusChanged:{
        if(status == CPageStatus.Show){
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
