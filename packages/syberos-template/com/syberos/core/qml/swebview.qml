import QtQuick 2.0
import QtWebKit 3.0
import QtWebKit.experimental 1.0
import com.syberos.basewidgets 2.0

WebView {

    id: webview

    focus: true
    anchors.top: parent.top

    property var syberObject

    signal receiveMessage(var message)

    signal downLoadConfirmRequest

    property var _contentY: 0
    property url curHoverUrl: ""

    anchors.bottom: parent.bottom
    width: parent.width

    //        experimental.userAgent:"Mozilla/5.0 (Linux; Android 4.0.3; HTC One X Build/IML74K) AppleWebKit/535.19 (KHTML, like Gecko) Chrome/18.0.1025.133 Mobile Safari/535.19"
    experimental.userAgent: "Mozilla/5.0 (Linux; Android 4.4.2; GT-I9505 Build/JDQ39) AppleWebKit/537.36 (KHTML, like Gecko) Version/1.5 Chrome/28.0.1500.94 Mobile Safari/537.36;SyberOS:1.0.0"
    experimental.minimumScale: false
    experimental.preferredMinimumContentsWidth: 720
    experimental.objectName: 'qml'

    experimental.preferences.navigatorQtObjectEnabled: true
    experimental.onMessageReceived: {
        console.log("----- ", "WebView received Message: ",
                    message.data, "\r\n")

        receiveMessage(message)
        //                    var model = JSON.parse(message.data);

        //                    var result;
        //                    if(model.data){
        //                        var keys = Object.keys(model.data);

        //                        var funcArgs = {};
        //                        for(var i in keys){
        //                            console.log("@@@ ", "key: ", i, keys[i], "\r\n")
        //                            console.log("@@@ value is",model.data[keys[i]]);
        //                            funcArgs[keys[i]] = model.data[keys[i]];
        //                        }

        //                       // NativeSdkManager.request("TestHandler*",model.callbackId,model.handlerName,funcArgs);
        //                    }
    }


    //experimental.itemSelector: ItemSelectorb{}
    experimental.alertDialog: CAlertDialog {
        id: messageDialog
        canceledOnOutareaClicked: false
        messageText: model.message
        onAccepted: {
            model.accept()
        }

        Component.onCompleted: {
            show()
        }
    }

    experimental.confirmDialog: CDialog {
        id: confirmDialog
        canceledOnOutareaClicked: false
        messageText: model.message
        onAccepted: {
            model.accept()
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

    experimental.promptDialog: CInputDialog {
        id: promptDialog
        canceledOnOutareaClicked: false
        titleText: model.message
        onAccepted: {
            model.accept(messageAreaItem.text)
        }
        onRejected: {
            model.reject()
        }
        onCanceled: {
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


    //                experimental.onPermissionRequested: {
    //                    permission.setAllow(browserServer.getSwitch() )
    //                }
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
    //html: "<script>window.qml.qmlCall();</script>"
    //url: "http://172.16.160.34:8002/jiaqznew/login.html"
    url: "file://" + helper.getWebRootPath() + "/index.html"
    onUrlChanged: {
        console.log("url is:", url)
    }

    onLoadProgressChanged: {
        console.log("onLoadProgressChanged", loadProgress)
    }

    Component.onCompleted: {
        console.log("Component.onCompleted====")
        webview.SetJavaScriptCanOpenWindowsAutomatically(false)
    }
}
