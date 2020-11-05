import QtQuick 2.1
import QtWebEngine 1.5
import com.syberos.basewidgets 2.0
import "permission.js" as Permission

CDialog {
    property var requestedFeature
    property url securityOrigin
    property WebEngineView view

    id: permissionBar
    visible: false
    acceptedButtonText: "同意"
    rejectButtonText: "拒绝"
    titleAreaEnabled: false

    onRejected: {
        view.grantFeaturePermission(securityOrigin, requestedFeature, false)
        //拒绝后,暂时不做保留
        //Permission.setPermission(securityOrigin, requestedFeature,false)
    }

    onAccepted: {
        view.grantFeaturePermission(securityOrigin, requestedFeature, true)
        Permission.setPermission(securityOrigin, requestedFeature, true)
    }

    function textForFeature(feature) {
        switch (feature) {
        case WebEngineView.Geolocation:
            return "网站 %1 想使用您当前的位置"
        case WebEngineView.MediaAudioCapture:
            return "%1 想要访问麦克风"
        case WebEngineView.MediaVideoCapture:
            return "%1 想要访问相机"
        case WebEngineView.MediaAudioVideoCapture:
            return "%1 想要访问麦克风和相机"
        case WebEngineView.DesktopVideoCapture:
            return "%1 想要捕获您的桌面视屏"
        case WebEngineView.DesktopAudioVideoCapture:
            return "%1 想要捕获您桌面的音频和视屏"
        case WebEngineView.Notifications:
            return "%1 想要显示通知"
        default:
            break
        }
        return '%1 想要您授权未知或不受支持的功能: ' + feature
    }

    onRequestedFeatureChanged: {
        permissionBar.messageText = textForFeature(requestedFeature).arg(
                    securityOrigin)
    }

}
