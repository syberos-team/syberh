import QtQuick 2.0
import QtWebKit 3.0
import QtQuick.Window 2.2
import QtWebKit.experimental 1.0
import com.syberos.basewidgets 2.0
import com.syberos.filemanager.filepicker 1.0
import "../js/util/log.js" as LOG
import "../js/syber.js" as Syberh

CPage{
    //加载信号
    signal onLoadProgress(var loadProgress)
    //返回键信号
    signal keyOnReleased(var event)
    //接受消息信号
    signal receiveMessage(var message)
    property var surl
    //是否能回退
    function canGoBack(){
        return swebview.canGoBack;
    }

    function canGoForward(){
        return swebview.canGoForward
    }
    //Go backward within the browser's session history, if possible. (Equivalent to the window.history.back() DOM method.)
    function goBack(){
        swebview.goBack();
    }
    //Go forward within the browser's session history, if possible. (Equivalent to the window.history.forward() DOM method.)
    function goForward(){
        swebview.goForward();
    }

    //return the swebview
    function getWebview(){
        return swebview
    }
    //Returns true if the HTML page is currently loading, false otherwise.
    function loading(){
        return swebview.loading;
    }
    //return swebview url
    function getCurrentUrl(){
        return swebview.url.toString();
    }
    //打开url
    function openUrl(url){
        LOG.logger.verbose('swebview openUrl()',url)
        if(swebview.loading){
            LOG.logger.verbose('swebview loading',swebview.loading)
            swebview.stop();
        }
        swebview.url=url;
    }
    //停止当前所有动作
    function stop(){
        swebview.stop();
    }
    //重新加载webview
    function reload(url){
        swebview.stop();
        swebview.reload();
    }
    //执行JavaScript代码
    function evaluateJavaScript(res){
        if(typeof res ==='string'){
            swebview.experimental.evaluateJavaScript(
                        'JSBridge._handleMessageFromNative(' + res + ')'
                        )
            return;
        }else{
            swebview.experimental.evaluateJavaScript(
                        'JSBridge._handleMessageFromNative(' + JSON.stringify(res) + ')'
                        )
        }

    }
    Keys.onReleased: {
        LOG.logger.verbose('SWebview qml Keys.onReleased',Keys.onReleased)
        keyOnReleased(event)
        //event.accepted = true
    }

    contentAreaItem:Rectangle{
        id:root
        anchors.fill:parent



        WebView {
            id: swebview
            focus: true
            signal downLoadConfirmRequest
            property url curHoverUrl: ""
            anchors.fill:parent
            url:surl
            experimental.userAgent: "Mozilla/5.0 (Linux; Android 4.4.2; GT-I9505 Build/JDQ39) AppleWebKit/537.36 (KHTML, like Gecko) Version/1.5 Chrome/28.0.1500.94 Mobile Safari/537.36;SyberOS:1.0.0"
            experimental.minimumScale: false
            experimental.preferredMinimumContentsWidth: Screen.width
            experimental.deviceWidth:Screen.width
            experimental.deviceHeight:Screen.height
            experimental.objectName: 'qml'
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
                curHoverUrl= hoveredUrl
            }
            property string navigateUrl: ""
            property string telNumber: ""
            onNavigationRequested: {
                var logger=LOG.logger;
                logger.verbose("onNavigationRequested request.navigationType:",request.navigationType)
                logger.verbose("onNavigationRequested",helper.getWebRootPath())
            }


            onUrlChanged: {
                LOG.logger.verbose('SWebview onUrlChanged',loadProgress)
            }

            onLoadProgressChanged: {
                LOG.logger.verbose('SWebview qml onLoadProgressChanged',loadProgress)
                onLoadProgress(loadProgress)
            }

            onSms: {
                LOG.logger.verbose("onSms", url, body);
                gApp.openUrl("sms:?body=" + body);
            }

            onMailto: {
                LOG.logger.verbose("onMailto url:[%s], body:[%s]", url, body);
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
            Component.onCompleted: {
                LOG.logger.verbose("SWebview Component.onCompleted")
                swebview.SetJavaScriptCanOpenWindowsAutomatically(false)
            }
        }
    }
    Component.onCompleted: {
        //设置是否显示状态栏，应与statusBarHoldItemEnabled属性一致
        gScreenInfo.setStatusBar(true);
        //设置状态栏样式，取值为"black"，"white"，"transwhite"和"transblack"
        //gScreenInfo.setStatusBarStyle("transblack");
    }
}
