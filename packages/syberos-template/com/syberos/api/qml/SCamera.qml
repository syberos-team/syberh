import QtQuick 2.0
import QtMultimedia 5.2
import com.syberos.basewidgets 2.0
import QtQuick.Window 2.2

CPage {
    id: cameraPage

    property string imgPath
    property var randomNum
    property bool isVideoMode: cameraObj.captureMode === Camera.CaptureVideo
    property bool isBackFace: currentCameraPosition === cameraPosition.back ? true : false
    property var cameraPosition: {"front": 1, "back": 0}
    property int currentCameraPosition: cameraPosition.back

    signal back(string path)

    Camera {
        id: cameraObj

        cameraPosition: Camera.BackFace //设置后置摄像头
        captureMode: Camera.CaptureStillImage //相机捕捉图片
        flash.mode: Camera.FlashRedEyeReduction //控制照相机闪光灯的方法和属性。红眼减少闪光
        imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash //调整相机图像处理参数的方法和属性。闪光白平衡模式

        focus {
            focusMode: Camera.FocusAuto
            focusPointMode: Camera.FocusPointAuto
            customFocusPoint: Qt.point(0.5, 0.5)
        }

        exposure {
            exposureCompensation: -1.0
            exposureMode: Camera.ExposurePortrait //曝光模式
        }

        imageCapture {
            //捕捉了图片，又没有保存到磁盘时，这个信号被发射
            onImageCaptured: {
                photoPreview.source = preview
            }
            //捕捉的图片被写入磁盘时，这个信号被发射
            onImageSaved: {
                //将应用下的图片复制到相册中，后删除应用中的图片
                randomNum = getRandomNum();
                NativeSdkManager.request('Camera*', randomNum, 'changeImagePath', {'path':path});
            }
            //捕捉请求出现错误
            onCaptureFailed: {
                console.log("image onCaptureFailed! reqId: " + requestId)
                console.log("image onCaptureFailed! message:  " + message)
            }
        }
    }

    // min:随机数的最小值，max:随机数的最大值
    function getRandomNum(){
        var Min = 10000000;
        var Max = 99999999;
        var Range = Max - Min;
        var Rand = Math.random();
        return(Min + Math.round(Rand * Range));
    }

    Connections{
        target: NativeSdkManager
        onSuccess:{
            if( parseInt(responseID) === parseInt(randomNum)){
                 imgPath = "file://" + result.imgPath;
                 photoPreviewRec.opacity = 1
                 photoPreview.source = imgPath
            }

        }
    }

    VideoOutput {
        id:camerVideoOutput
        source: cameraObj
        orientation: -90 //摄像头旋转90度
        focus: visible // 接收焦点并在可见时捕获关键事件
        width: isVideoMode ?  isBackFace? height*9/16: height*2/3 : height*3/4
        transform: Rotation {
            id: camerRotation
            origin.x: width / 2
            origin.y: 100
            axis.x: 0; axis.y: 1; axis.z: 0
            angle: currentCameraPosition === cameraPosition.back ? 0 : 180
            Behavior on angle { PropertyAnimation{} }
        }
    }

    Rectangle {
        id:photoPreviewRec
        anchors.fill: parent
        color: "black"
        opacity:0

        Image {
            id: photoPreview
            rotation: +90
            anchors.centerIn: parent
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
//            fillMode: Image.PreserveAspectCrop
            height: Screen.width
            width: Screen.height

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    photoPreviewRec.opacity = 0
                    photoPreview.source = ""
                }
            }
        }
    }
    //底部靠左 返回不保存操作
    Rectangle {
        id: backRect
        width: 65 * 2
        height: width
        radius: 65 //弧度大小
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 50

        MouseArea {
            anchors.fill: parent
            onClicked: {
                cameraObj.stop() //返回前关闭相机功能
                back(null)
            }
        }

        Image {
            id: backImg
            source: "/res/back.png"
            anchors.fill: parent
        }
    }

    //底部居中 拍照操作
    Rectangle {
        id: captureRect
        width: 65 * 2
        height: width
        radius: 65 //弧度大小
        anchors.bottomMargin: 40
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        MouseArea {
            anchors.fill: parent
            visible: cameraObj.imageCapture.ready
            onClicked: cameraObj.imageCapture.capture()
        }

        Image {
            id: captureImg
            source: "/res/start.png"
            anchors.fill: parent
        }
    }

    //底部靠右 返回保存操作
    Rectangle {
        id: saveRect
        width: 65 * 2
        height: width
        radius: 65 //弧度大小
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.right: parent.right
        anchors.rightMargin: 50

        MouseArea {
            anchors.fill: parent
            onClicked: {
                cameraObj.stop() //返回前关闭相机功能
                back(imgPath)
            }
        }

        Image {
            id: saveImg
            source: "/res/save.png"
            anchors.fill: parent
        }
    }

    //左上角 切换摄像头操作
    Rectangle {
        id: switchRect
        width: 35 * 2
        height: width
        radius: 35 //弧度大小
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 10

        MouseArea {
            anchors.fill: parent
            onClicked: {
                var postition = cameraObj.cameraPosition
                //切换摄像头方法：关闭当前摄像头、设置成要切换的摄像头、调整摄像头角度、开启摄像头
                if (postition === 1) {
                    cameraObj.stop();
                    cameraObj.cameraPosition = Camera.FrontFace
                    camerVideoOutput.orientation = +90
                    photoPreview.rotation = -90
                   cameraObj.start();
                } else if (postition === 2) {
                    cameraObj.stop();
                    cameraObj.cameraPosition = Camera.BackFace
                    camerVideoOutput.orientation = -270
                    photoPreview.rotation = +270
                    cameraObj.start();
                }
            }
        }

        Image {
            id: switchImg
            source: "/res/switch.png"
            anchors.fill: parent
        }
    }

    Component.onCompleted: {
        cameraObj.stop()
        cameraObj.start()
    }
}
