import QtQuick 2.0
import QtMultimedia 5.2
import com.syberos.basewidgets 2.0

Item {
    anchors.fill: parent
    Camera {
        id: camera1
        captureMode:Camera.CaptureStillImage//相机捕捉图片
        imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash //调整相机图像处理参数的方法和属性。闪光白平衡模式

        exposure {
            exposureCompensation: -1.0
            exposureMode: Camera.ExposurePortrait//曝光模式
        }

        flash.mode: Camera.FlashRedEyeReduction//控制照相机闪光灯的方法和属性。红眼减少闪光

        imageCapture {
            onImageCaptured: {
                photoPreview.source = preview  //在图像中显示预览
            }
        }
    }

    VideoOutput {
        source: camera1
        anchors.fill: parent
        focus : visible // 接收焦点并在可见时捕获关键事件
    }

    Image {
        id: photoPreview
    }
//    Component.onCompleted: {
//        camera1.start();
//    }
}
