import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: sChooseImagePage
    // 取消信号
    signal imageCancel()

    // 选取图片成功信号
    signal receiveImageUrls(string urls)

    // 选取图片成功信号
    signal chooseCameraSuccess(string filePath)

    // 相机取消信号
    signal chooseCameraCancel()

    // album 取消信号
    signal chooseAlbumCancel()

    function open(obj) {
        sChooseImage.open(obj)
    }

    SChooseImage {
        id: sChooseImage

        onCancel: {
            sChooseImagePage.imageCancel()
            pageStack.pop()
        }

        onReceiveUrls: {
            console.log("SChooseImagePage.qml urls***********", JSON.stringify(urls))
            sChooseImagePage.receiveImageUrls(JSON.stringify(urls))
            pageStack.pop()
        }

        onCameraSuccess: {
            console.log("SChooseImagePage.qml filePath***********", JSON.stringify(filePath))
            sChooseImagePage.chooseCameraSuccess(JSON.stringify(filePath))
            pageStack.pop()
        }

        onCameraCancel: {
           sChooseImagePage.chooseCameraCancel()
            pageStack.pop()
        }

        onAlbumCancel: {
            sChooseImagePage.chooseAlbumCancel()
            pageStack.pop()
        }
    }
}

