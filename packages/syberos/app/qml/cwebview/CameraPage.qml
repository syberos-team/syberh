import QtQuick 2.0
import com.syberos.basewidgets 2.0
import com.syberos.multimedia.camera 2.0

CameraPlugin {

    signal confirmed(string image, bool isFullImage)
    signal cancelled()

    property Item parentItem

    enableCut: false

    onImageConfirmed: {
        if(image){
            confirmed(image, isFullImage)
            if(parentItem){
                pageStack.pop()
            }
        }
    }

    Component.onDestruction: {
        cancelled()
    }
}
