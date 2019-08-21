import QtQuick 2.0
import QtWebKit 3.0
import QtQuick.Window 2.2
import QtWebKit.experimental 1.0
import com.syberos.basewidgets 2.0

WebView {
    id: webview
    focus: true
    property var syberObject
    //接受消息信号
    signal receiveMessage(var message)
    signal downLoadConfirmRequest
     //加载信号
    signal reloadSuccess(var loadProgress)
    //返回键信号
    signal keyOnReleased(var event)
    property var _contentY: 0
    property url curHoverUrl: ""
    //
    anchors.topMargin: gScreenInfo.statusBarHeight
    anchors.fill:parent

    experimental.userAgent: "Mozilla/5.0 (Linux; Android 4.4.2; GT-I9505 Build/JDQ39) AppleWebKit/537.36 (KHTML, like Gecko) Version/1.5 Chrome/28.0.1500.94 Mobile Safari/537.36;SyberOS:1.0.0"
    experimental.minimumScale: false
    experimental.preferredMinimumContentsWidth: Screen.width
    experimental.deviceWidth:Screen.width
    experimental.deviceHeight:Screen.height
    experimental.objectName: 'qml'
    Keys.onReleased: {
        console.log("----- ", "WebView (event): ",
                    event.key, "\r\n")
        keyOnReleased(event)
        //event.accepted = true
    }

    experimental.preferences.navigatorQtObjectEnabled: true
    experimental.onMessageReceived: {
        console.log("----- ", "WebView received Message: ",
                    message.data, "\r\n")

        receiveMessage(message)

    }
    experimental.alertDialog: SAlert {
        id: salert
        messageText: model.message
        onAccepted: {
            model.accept()
        }

        Component.onCompleted: {
            show()
        }
    }


    experimental.confirmDialog: SConfirm {
        id: confirmDialog
        messageText: model.message
        onAccepted: {
            model.accept()
        }
        onRejected: {
            model.reject()
        }

        Component.onCompleted: {
            show()
        }
    }

    experimental.promptDialog: SPrompt {
        id: promptDialog
        messageText: model.message
        onAccepted: {
            model.accept(inputText)
        }
        onRejected: {
            model.reject()
        }

        Component.onCompleted: {
            setText(model.defaultValue)
            show()
        }
    }

    experimental.authenticationDialog: CInputDialog {
        id: authDialog
        canceledOnOutareaClicked: false
        titleText: model.hostname + ":\n" + model.realm

        messageAreaComponent: Column {
            property alias nameText: nameEdit.text
            property alias passText: password.text
            CLineEdit {
                id: nameEdit
                width: authDialog.width - messageAreaLeftMargin - messageAreaRightMargin
                echoMode: TextInput.Normal
                inputMethodHints: authDialog.inputMethodHints
                maximumLength: authDialog.maximumLength
                onTextChanged: {
                    authDialog.textChanged(text)
                }
            }
            CLine {
                width: parent.width
                height: 2
            }

            CLineEdit {
                id: password
                width: authDialog.width - messageAreaLeftMargin - messageAreaRightMargin
                echoMode: TextInput.Password
                inputMethodHints: authDialog.inputMethodHints
                maximumLength: authDialog.maximumLength
                onTextChanged: {
                    authDialog.textChanged(text)
                }
            }

            CLine {
                width: parent.width
            }
        }
        onAccepted: {
            model.accepted(messageAreaItem.nameText, messageAreaItem.passText)
        }
        onRejected: {
            model.reject()
        }
        onCanceled: {
            model.reject()
        }

        Component.onCompleted: {
            show()
        }
    }

    experimental.preferences.minimumFontSize: 13
    experimental.gpsEnable: false

    property bool _autoLoad: true
    experimental.preferences.autoLoadImages: true //webviewManager.wifiStatus?true:((typeof setupMgr != undefined)?(setupMgr.getValue("autoloadimage",true)=="true"?true:false):false)

    onLinkHovered: {
        curHoverUrl = hoveredUrl
    }
    property string navigateUrl: ""
    property string telNumber: ""
    onNavigationRequested: {
        console.log("$$$$$$$$$$$$$$$onNavigationRequested:",
                    request.navigationType)
    }

    url: "file://" + helper.getWebRootPath() + "/index.html"
    onUrlChanged: {
        console.log("url is:", url)
    }

    onLoadProgressChanged: {
        console.log("onLoadProgressChanged", loadProgress)
        reloadSuccess(loadProgress)
       
    }

    Component.onCompleted: {
        console.log("Component.onCompleted====")
        webview.SetJavaScriptCanOpenWindowsAutomatically(false)
    }
}
