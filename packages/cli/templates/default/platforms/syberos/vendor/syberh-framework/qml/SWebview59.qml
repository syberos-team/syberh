import QtQuick 2.0
import QtQuick.Window 2.2
import com.syberos.filemanager.filepicker 1.0
import com.syberos.basewidgets 1.0
import com.syberos.basewidgets 2.0
import syberh_filepicker 1.0
import QtQml.Models 2.2
import QtWebEngine 1.5
import QtWebChannel 1.0

import "../js/util/log.js" as LOG
import "./"
import "./CMenu"


CPage{
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
            swebview.runJavaScript('JSBridge._handleMessageFromNative(' + res + ')', function(result){
              LOG.logger.verbose('evaluateJavaScript:', res, 'result:', result);
            })
        }else{
            var param = JSON.stringify(res)
            swebview.runJavaScript('JSBridge._handleMessageFromNative(' + param + ')', function(result){
              LOG.logger.verbose('evaluateJavaScript:', param, 'result:', result);
            })
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
        ObjectModel {
            id: trans
            WebChannel.id: "trans"

            function postMessage(msg){
                LOG.logger.verbose('trans postMessage ', msg)
                receiveMessage(msg)
            }
        }

        WebChannel {
            id: channel
            registeredObjects: [trans]
        }

        WebEngineView {
            id: swebview
            focus: true
            // zoomFactor: 3.0
            signal downLoadConfirmRequest
            property url curHoverUrl: ""

            anchors {
                top: sNavigationBar.visible ? sNavigationBar.bottom : parent.top
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            url:surl
            webChannel: channel

            profile: WebEngineProfile{
              httpUserAgent: "Mozilla/5.0 (Linux; Android 5.0; SM-G900P Build/LRX21T) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3770.100 Mobile Safari/537.36 SyberOS " + helper.aboutPhone().osVersionCode + " " + helper.getQtVersion() +";"
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

            onLoadingChanged: function(loadRequest){
                LOG.logger.verbose('SWebview qml onLoadingChanged',loadRequest.status,loadRequest.url)
                if (!loading && loadRequest.status === WebEngineView.LoadFailedStatus){
                    LOG.logger.error('SWebview qml onLoadingChanged 加载失败')
                    //swebview.loadHtml("加载失败 " + loadRequest.url, "", loadRequest.url)
                    //swebview.reload();
                }
                if(!loading && loadRequest.status===WebEngineView.LoadSucceededStatus){
                    sloadingChanged(loadRequest);
                }

            }

            onJavaScriptConsoleMessage: function(level, message, lineNumber, sourceID){
              switch(level){
                case WebEngineView.InfoMessageLevel:
                  LOG.logger.verbose('line:', lineNumber, 'sourceID:', sourceID, 'msg:', message)
                  break;
                case WebEngineView.WarningMessageLevel:
                  LOG.logger.warn('line:', lineNumber, 'sourceID:', sourceID, 'msg:', message)
                  break;
                case WebEngineView.ErrorMessageLevel:
                  LOG.logger.error('line:', lineNumber, 'sourceID:', sourceID, 'msg:', message)
                  break;
              }
            }

            onJavaScriptDialogRequested: function(request){
              request.accepted = true;
              switch(request.type){
                case JavaScriptDialogRequest.DialogTypeAlert:
                  salert.request = request;
                  salert.titleText = request.title
                  salert.messageText = request.message
                  salert.show();
                  break;
                case JavaScriptDialogRequest.DialogTypeConfirm:
                  confirmDialog.request = request;
                  confirmDialog.titleText = request.title
                  confirmDialog.messageText = request.message
                  confirmDialog.show();
                  break;
                case JavaScriptDialogRequest.DialogTypePrompt:
                  promptDialog.request = request;
                  promptDialog.titleText = request.message
                  promptDialog.setText(request.defaultText);
                  promptDialog.show();
                  break;
                case JavaScriptDialogRequest.DialogTypeUnload:
                  LOG.logger.verbose('用户离开页面询问尚未实现')
                  break;
              }
            }

            onFileDialogRequested: function(request){
              LOG.logger.verbose('onFileDialogRequested >>>>>>>>>>>>>>>>>>>>>文件选择')
              console.log('onFileDialogRequested >>>>>>>>>>>>>>>>>>>>>文件选择')
              request.accepted = true
              salert.messageText = '请调用filepicker API实现'
              salert.show()
            }

            onAuthenticationDialogRequested: function(request){
              request.accepted = true;
              authDialog.request = request;
              switch(request.type){
                case WebEngineAuthenticationDialogRequest.AuthenticationTypeHTTP:
                  authDialog.titleText = request.url + ":\n" + request.realm;
                  break;
                case WebEngineAuthenticationDialogRequest.AuthenticationTypeProxy:
                  authDialog.titleText = request.proxyHost + ":\n" + request.realm;
                  break;
              }
              authDialog.clear();
              authDialog.show();
            }

            onContextMenuRequested: function(request) {
                console.log('******onContextMenuRequested******')
                request.accepted = true;
                myMenu.x = request.x;
                myMenu.y = request.y;
                myMenu.trigger.connect(view.triggerWebAction);
                myMenu.popup();
            }
        }

        SAlert {
            id: salert
            property JavaScriptDialogRequest request
            titleText: ''
            messageText: ''
            onAccepted: {
                request.dialogAccept()
            }
        }
        SConfirm {
            id: confirmDialog
            property JavaScriptDialogRequest request
            titleText: ''
            messageText: ''
            onAccepted: {
                request.dialogAccept()
            }
            onRejected: {
                request.dialogReject()
            }
        }
        CInputDialog{
            id: promptDialog
            property JavaScriptDialogRequest request
            canceledOnOutareaClicked: false
            titleText: ''
            onAccepted: {
                request.dialogAccept(messageAreaItem.text)
            }
            onRejected: {
                request.dialogReject()
            }
            onCanceled: {
                request.dialogReject()
            }
        }

        // SFilesPicker {
        //     id: picker
        //     property FileDialogRequest request
        //     titleText: "文件选择"
        //     leftItemEnabled: true
        //     count: 1

        //     Keys.onReleased: {
        //         if (event.key == Qt.Key_Back || event.key == Qt.Key_Escape) {
        //             console.log('***********Keys.onReleased**Key_Back******')
        //             LOG.logger.verbose('***********Keys.onReleased**Key_Back******')
        //             event.accepted =true;
        //             picker.request.dialogReject();
        //         }
        //     }

        //     // function show(){
        //     //     parent = gAppUtils.pageStackWindow
        //     //     visible = true
        //     //     status = 2
        //     //     focus = true
        //     //     LOG.logger.verbose('onFileDialogRequested >>>>>>>>>>>>>>>>>>>>>文件选择*****show')
        //     //    console.log('onFileDialogRequested >>>>>>>>>>>>>>>>>>>>>文件选择*****show')
        //     // }
        // }
        CInputDialog {
            id: authDialog
            property AuthenticationDialogRequest request
            canceledOnOutareaClicked: false
            titleText: ''
            messageAreaComponent: Column {
                property alias nameText: nameEdit.text
                property alias passText: password.text
                CLineEdit {
                    id: nameEdit
                    width: authDialog.width - authDialog.messageAreaLeftMargin - authDialog.messageAreaRightMargin
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
                    width: authDialog.width - authDialog.messageAreaLeftMargin - authDialog.messageAreaRightMargin
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
                request.dialogAccept(messageAreaItem.nameText, messageAreaItem.passText)
            }
            onRejected: {
                request.dialogReject()
            }
            onCanceled: {
                request.dialogReject()
            }
            function clear(){
              messageAreaItem.nameText = "";
              messageAreaItem.passText = "";
            }
        }
    }

    Component.onCompleted: {

        WebEngine.settings.webGLEnabled = true;
        swebview.settings.webGLEnabled = true;
        console.log('Screen--', JSON.stringify(Screen))

        console.log('gScreenInfo--', JSON.stringify(gScreenInfo))

        // 设置缩放比例
        swebview.zoomFactor = gScreenInfo.density
        
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
