import QtQuick 2.0
import QtWebKit 3.0
import QtQuick.Window 2.2
import QtWebKit.experimental 1.0
import com.syberos.basewidgets 2.0
import com.syberos.filemanager.filepicker 1.0
import "../js/util/log.js" as LOG

WebView {
    id: webview
    focus: true
    //接受消息信号
    signal receiveMessage(var message)
    signal downLoadConfirmRequest
    //加载信号
    signal reloadSuccess(var loadProgress)
    //返回键信号
    signal keyOnReleased(var event)
    property var _contentY: 0
    property url curHoverUrl: ""
    property var syberObject
    anchors.topMargin: gScreenInfo.statusBarHeight
    anchors.fill:parent

    experimental.userAgent: "Mozilla/5.0 (Linux; Android 4.4.2; GT-I9505 Build/JDQ39) AppleWebKit/537.36 (KHTML, like Gecko) Version/1.5 Chrome/28.0.1500.94 Mobile Safari/537.36;SyberOS:1.0.0"
    experimental.minimumScale: false
    experimental.preferredMinimumContentsWidth: Screen.width
    experimental.deviceWidth:Screen.width
    experimental.deviceHeight:Screen.height
    experimental.objectName: 'qml'
    Keys.onReleased: {
        LOG.logger.verbose('SWebview qml Keys.onReleased',Keys.onReleased)
        console.log("----- ", "WebView (event): ",
                    event.key, "\r\n")
        keyOnReleased(event)
        //event.accepted = true
    }

    experimental.preferences.navigatorQtObjectEnabled: true
    experimental.onMessageReceived: {

        receiveMessage(message)

    }

    experimental.itemSelector:ItemSelector{}

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

    experimental.promptDialog: CInputDialog{
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

        Component.onCompleted:{
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
    experimental.filePicker: SyberosFilesPicker{
        id: picker
        width: gAppUtils.pageStackWindow.width
        height: gAppUtils.pageStackWindow.height

        Connections {
            target: picker
            onOk: {
                console.log("on ok", picker.status)
                console.log("on Page set file save path", picker.dirPath)
                model.accept(picker.filesPath);
            }
            onCancel: {
                model.rejected();
            }
        }

        Keys.onReleased: {
            if (event.key == Qt.Key_Back || event.key == Qt.Key_Escape) {
                model.rejected();
                event.accepted =true;
            }
        }

        Component.onCompleted:{
            parent = gAppUtils.pageStackWindow;
            visible = true;
            status = CPageStatus.WillShow;
            focus = true
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

        console.log('--------------helper.getWebRootPath()',helper.getWebRootPath())
    }

    url: "file://" + helper.getWebRootPath() + "/index.html"
    onUrlChanged: {
        console.log("url is:", url)
    }

    onLoadProgressChanged: {
        LOG.logger.verbose('SWebview qml onLoadProgressChanged',loadProgress)
        reloadSuccess(loadProgress)

    }

    Component.onCompleted: {
        console.log("Component.onCompleted====")
        webview.SetJavaScriptCanOpenWindowsAutomatically(false)
    }

    onSms: {
        console.log("onsmsonsmonsmonsmonsmonsmonsmonsmonsmonsmonsmssssssssss", url, body);
        gApp.openUrl("sms:?body=" + body);
    }

    onMailto: {
        console.log("onMailtoonMailtonMailtonMailtonMailtonMailtonMailtonMailto", url, body);
        gApp.openUrl("email:writeMail?address="+ url + "&content=" + body + "&attach=");
    }

    onTel: {
        //电话拨打功能,暂未实现
        //console.log("onTelonTeonTeonTeonTeonTeonTeonTeonTeonTeonTeonTelllllllllll", telNum);
        //        telNumber = telNum;
        //        if (!gAppUtils.pageStackWindow.confirmDialog)
        //        {
        //            gAppUtils.pageStackWindow.createConfirmDialog(mainPage)
        //        }

        //        gAppUtils.pageStackWindow.confirmDialog.messageText = os.i18n.ctr(qsTr("are you sure to call the number: ")) + telNum  //确定呼叫:
        //        gAppUtils.pageStackWindow.confirmDialog.requestShow()
        //        confirmDialogOfDial.target = gAppUtils.pageStackWindow.confirmDialog
    }
}
