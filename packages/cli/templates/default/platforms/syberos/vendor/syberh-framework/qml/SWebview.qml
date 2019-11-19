import QtQuick 2.0
import QtWebKit 3.0
import QtQuick.Window 2.2
import QtWebKit.experimental 1.0
import com.syberos.filemanager.filepicker 1.0
import org.nemomobile.voicecall 1.0
import com.syberos.basewidgets 1.0
import com.syberos.basewidgets 2.0
import syberh_filepicker 1.0

import "../js/util/log.js" as LOG
import "./"
import "./CMenu"


CPage{
    orientationPolicy:CPageOrientation.Automatic
    id: webView
    //加载进度信号
    signal sloadProgress(var loadProgress)

    //加载信号
    signal sloadingChanged(var loadRequest)
    //返回键信号
    signal keyOnReleased(var event)
    //接受消息信号
    signal receiveMessage(var message)
    //导航栏关闭信号
    signal navigationBarClose()

    property string surl:""

    //页面标题
    property string title: ""

    //背景色
    property string color: ""

    // 导航栏标题
    property string navigationBarTitle: ""

    // 标题文字居中居左 (日后使用)
//    property string navigationBarTitlePosition: ""

    // 导航栏背景色
    property string navigationBarColor: ""

    // 导航栏字体颜色
    property string navigationBarTextColor: ""

    // 返回按钮是否展示
    property bool navigationBarBackIconEnable: true

    // 关闭按钮是否展示
    property bool navigationBarCloseIconEnable: true

    //设置背景色
    function setBackgroundColor(color){
        root.color = color;
    }

    // 展示navigatorBar
    function showNavigatorBar(options){
       sNavigationBar.show(options);
    }

    // 设置NavigationBar Title
    function setNavigationBarTitle(title) {
        //设置navigatorBar title
        LOG.logger.verbose('setNavigationBarTitle-title-',title);
        sNavigationBar.setTitle(title);
    }

    // 设置NavigationBar 背景颜色和字体颜色
    function setNavigationBarColor(options) {
        //设置navigatorBar title
        LOG.logger.verbose('setNavigationBarColor-color-',color);
        if (options.color) {
            sNavigationBar.setColor(options.color);
        }
        if (options.textColor) {
            sNavigationBar.setTextColor(options.textColor);
        }
    }

    // 获取导航栏是否可用
    function getNavigationBarStatus() {
        return sNavigationBar.visible
    }

    function clearHistory(){
        //TODO 暂无找到实现方式
    }
    //是否能回退
    function canGoBack(){
        return swebview.canGoBack;
    }

    //删除所有cookies
    function deleteAllCookies()
    {
        swebview.experimental.deleteAllCookies()
    }

    function canGoForward(){
        return swebview.canGoForward
    }

    //Go backward within the browser's session history, if possible. (Equivalent to the window.history.back() DOM method.)
    function goBack(){
        swebview.goBack();
        swebview.forceActiveFocus()
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
        if(swebview.url.toString()===url){
            return;
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
        swebview.forceActiveFocus()
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
        SNavigationBar{
            id: sNavigationBar
            closeCurWebviewEnable: swebview.canGoBack
            onGoBack: {
                if(swebview.canGoBack) {
                    // 当前webview有history && history.length>1，走这里返回上一个history
                    swebview.goBack();
                } else {
                    // 当前webview有history && history.length==1，直接关闭当前webview
                    navigationBarClose();
                }
            }
            onCloseCurWebview:{
                navigationBarClose();
            }
        }
        WebView {
            id: swebview
            focus: true
            signal downLoadConfirmRequest
            property url curHoverUrl: ""
            anchors {
                top: sNavigationBar.visible ? sNavigationBar.bottom : parent.top
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            url:surl
            onTitleChanged: {
                console.log('--swebview--title', title);
            }

            experimental.userAgent: "Mozilla/5.0 (Linux; Android 4.4.2; GT-I9505 Build/JDQ39) SyberOS "+helper.aboutPhone().osVersionCode+ " " + helper.getQtVersion() + ";"
            experimental.minimumScale: false
            experimental.preferredMinimumContentsWidth: Screen.width
            experimental.deviceWidth:Screen.width
            experimental.deviceHeight:Screen.height
            experimental.preferences.navigatorQtObjectEnabled: true
            experimental.preferences.webGLEnabled: true
            experimental.preferences.webAudioEnabled: true
            experimental.preferences.minimumFontSize: 13
            experimental.gpsEnable: false
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

            // syberh_filepicker包里面引入
            experimental.filePicker: SFilesPicker {
                id: picker
                titleText: "文件选择"
                leftItemEnabled: true
                count: allowMultipleFiles?30:1

                Connections {
                    target: picker
                    onOk: {
                        model.accept(picker.filesPath);
                    }
                    onCancel: {
                        model.reject();
                    }
                }

                Keys.onReleased: {
                    if (event.key == Qt.Key_Back || event.key == Qt.Key_Escape) {
                        model.rejected();
                        event.accepted =true;
                    }
                }

                Component.onCompleted:{
                    parent = gAppUtils.pageStackWindow
                    visible = true
                    status = 2
                    focus = true
                }
            }


            experimental.onMessageReceived: {
                receiveMessage(message)
            }
            property bool _autoLoad: true

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
                sloadProgress(loadProgress)
            }

            onLoadingChanged:{
                LOG.logger.verbose('SWebview qml onLoadingChanged',loadRequest.status,loadRequest.url)
                if (!loading && loadRequest.status === WebView.LoadFailedStatus){
                    LOG.logger.error('SWebview qml onLoadingChanged 加载失败')
                    //swebview.loadHtml("加载失败 " + loadRequest.url, "", loadRequest.url)
                    //swebview.reload();
                }
                if(!loading && loadRequest.status===WebView.LoadSucceededStatus){
                    sloadingChanged(loadRequest);
                }

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

            //            onSelectChange: {
            //                    //console.log("webview.onSelectChange====--------------------------",rect)
            //                    textPrssMenu.visible = false;
            //                   BSelectTool.setCursor(swebview,show,rect);
            //             }
            Component.onCompleted: {
                LOG.logger.verbose("SWebview Component.onCompleted")
                swebview.SetJavaScriptCanOpenWindowsAutomatically(false)
            }
        }

    }


    Component.onCompleted: {
        //设置是否显示状态栏，应与statusBarHoldItemEnabled属性一致
        gScreenInfo.setStatusBar(true);
        console.log('swebview-navigationBarColor-', navigationBarColor)
        console.log('swebview-navigationBarTitle-', navigationBarTitle)
        console.log('swebview-navigationBarTextColor-', navigationBarTextColor)
        console.log('swebview-navigationBarBackIconEnable-', navigationBarBackIconEnable)
        console.log('swebview-navigationBarCloseIconEnable-', navigationBarCloseIconEnable)
        console.log('swebview-color-', color)

        if (color) {
            setBackgroundColor(color)
        }

        if (navigationBarTitle) {
            showNavigatorBar({
                navigationBarTitle: navigationBarTitle,
                navigationBarColor: navigationBarColor,
                navigationBarTextColor: navigationBarTextColor,
                navigationBarBackIconEnable: navigationBarBackIconEnable,
                navigationBarCloseIconEnable: navigationBarCloseIconEnable
            })
        }

        //设置状态栏样式，取值为"black"，"white"，"transwhite"和"transblack"
        //gScreenInfo.setStatusBarStyle("transblack");
    }
}