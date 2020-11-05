import QtQuick 2.0
import QtQuick.Window 2.2
import com.syberos.basewidgets 2.0
import QtQml.Models 2.2
import QtWebEngine 1.5
import QtWebChannel 1.0

import "../js/util/log.js" as LOG
import "../cwebview"
import "../"

CPage{
    objectName: "webView"
    id: webView
    // 屏幕自动旋转
    orientationPolicy: CPageOrientation.Automatic
    //加载进度信号
    signal sloadProgress(var loadProgress)
    //加载信号
    signal sloadingChanged(var loadRequest)
    // 按键信号
    signal skeyEvent(string eventType, var event)
    //接受消息信号
    signal receiveMessage(var message)
    //导航栏关闭信号
    signal navigationBarClose()
    // 屏幕旋转信号
    signal orientation(var pageOrientation)

    property string surl:""

    //页面标题
    property string title: ""

    //背景色
    property string backgroundColor: ""

    // 导航栏标题
    property string navigationBarTitle: ""

    // 标题文字居中居左 (日后使用)
//    property string navigationBarTitlePosition: ""

    // 导航栏背景色
    property string navigationBarBackgroundColor: ""

    // 导航栏字体颜色
    property string navigationBarColor: ""

    // 返回按钮是否展示
    property bool navigationBarBackIconEnable: true

    // 关闭按钮是否展示
    property bool navigationBarCloseIconEnable: true

    // 关闭按钮是否展示
    property bool pageHide: false

    // 页面是否销毁
    property bool isDestroy: false

    // 设置销毁状态
    function setDestroyStatus(status) {
        isDestroy = true;
    }

    //设置背景色
    function setBackgroundColor(color){
        swebview.backgroundColor = color;
    }

    // 展示navigatorBar
    function showNavigatorBar(options){
       sNavigationBar.show(options);
       swebview.anchors.topMargin = sNavigationBar.navigationBarHeight
    }

    // 设置NavigationBar Title
    function setNavigationBarTitle(title) {
        //设置navigatorBar title
        LOG.logger.verbose('setNavigationBarTitle-title- %s',title);
        sNavigationBar.setTitle(title);
    }

    // 设置NavigationBar 背景颜色和字体颜色
    function setNavigationBarColor(options) {
        //设置navigatorBar title
        LOG.logger.verbose('setNavigationBarColor-- %j', options);
        if (options.backgroundColor) {
            sNavigationBar.setBackgroundColor(options.backgroundColor);
        }
        if (options.color) {
            sNavigationBar.setColor(options.color);
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
        LOG.logger.verbose('swebview openUrl(%s)', url)
        if(swebview.loading){
            LOG.logger.verbose('swebview loading %s', swebview.loading)
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
              LOG.logger.verbose('evaluateJavaScript: %s  result: %s', res, result);
            })
        }else{
            var param = JSON.stringify(res)
            swebview.runJavaScript('JSBridge._handleMessageFromNative(' + param + ')', function(result){
              LOG.logger.verbose('evaluateJavaScript: %s  result: %s', param, result);
            })
        }

    }

    // 获取页面旋转方向, 默认是自动旋转(0)
    function getPageOrientation() {
        return webView.orientationPolicy || CPageOrientation.Automatic
    }

    // 设置页面旋转方向 1: 竖屏 2：横屏 默认： 跟着设备旋转
    function setPageOrientation(orientation) {
        if (orientation == 1) {
            if(projectConfig.statusBarShow()){
                webView.statusBarHoldEnabled = true
                gScreenInfo.setStatusBar(true);
             }else{
                 webView.statusBarHoldEnabled = false
             }
            webView.orientationPolicy = CPageOrientation.LockPortrait
        } else if(orientation == 2 || orientation == 8) {
            webView.statusBarHoldEnabled = false
            gScreenInfo.setStatusBar(false);
            webView.orientationPolicy = orientation == 2 ? CPageOrientation.LockLandscape : CScreenInfo.LandscapeInverted
        } else {
            webView.orientationPolicy = CPageOrientation.Automatic
        }
        console.log('orientation---webView.orientationPolicy---', orientation, webView.orientationPolicy, CPageOrientation.LockLandscape)
    }

    // 关联屏幕旋转信号(被动旋转是gScreenInfo.currentOrientation， 主动旋转webView.orientationPolicy)
    Connections {
        target: gScreenInfo
        ignoreUnknownSignals: true
        onCurrentOrientationChanged: {
            console.log('屏幕切换接收到信号了×××××××××××××××××××××', webView.orientationPolicy, gScreenInfo.currentOrientation, surl, pageHide, isDestroy)
            // 如果页面销毁，在这里拦截
            if (isDestroy) return
            webView.orientation({
              pageOrientation: webView.orientationPolicy,
              appOrientation: gScreenInfo.currentOrientation,
              // url 要拿webview的url值，因为redirectTo等这种情况下会直接修改webview的url值（surl可能不准确）
              url: swebview.url.toString()
            })
            // 横屏需要隐藏状态栏
            if(gScreenInfo.currentOrientation == CScreenInfo.Landscape
                || gScreenInfo.currentOrientation == CScreenInfo.LandscapeInverted
                || webView.orientationPolicy == CScreenInfo.Landscape
                || webView.orientationPolicy == CScreenInfo.LandscapeInverted
              ) {
                console.log('监听到信号*****************横屏')
                console.log('是否有键盘---', gInputContext.softwareInputPanelVisible)
                webView.statusBarHoldEnabled = false
                gScreenInfo.setStatusBar(false);
                 if(gInputContext.softwareInputPanelVisible) {
                     webView.anchors.bottomMargin = -140
                 } else {
                     webView.anchors.bottomMargin = 0
                 }
            } else {
                console.log('监听到信号*****************竖屏')
                if(projectConfig.statusBarShow()){
                    webView.anchors.bottomMargin = 0
                    webView.statusBarHoldEnabled = true
                    gScreenInfo.setStatusBar(true);
                    gScreenInfo.setStatusBarStyle(projectConfig.statusBarStyle());

                }else{
                    webView.statusBarHoldEnabled = false
                    if(gInputContext.softwareInputPanelVisible) {
                     webView.anchors.bottomMargin = -142
                     } else {
                         webView.anchors.bottomMargin = 0
                    }
                }
            }
        }
    }

    Keys.onReleased: {
        LOG.logger.verbose('SWebview qml Keys.onReleased %s %s', event.key, event.text)
        skeyEvent('onReleased', event)
    }

    Keys.onPressed: {
        LOG.logger.verbose('SWebview qml Keys.onPressed %s %s', event.key, event.text)
        skeyEvent('onPressed', event)
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
                LOG.logger.verbose('trans postMessage: %s', msg)
                receiveMessage(msg)
            }
        }

        WebChannel {
            id: channel
            registeredObjects: [trans]
        }

        CWebView {
            id: swebview
            focus: true
            property url curHoverUrl: ""

            anchors {
                top: root.top
                left: root.left
                right: root.right
                bottom: root.bottom
            }
            url:surl
            webChannel: channel

            profile: WebEngineProfile{
              httpUserAgent: "Mozilla/5.0 (Linux; Android 5.0; SM-G900P Build/LRX21T) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3770.100 Mobile Safari/537.36 SyberOS 4.1.1 5.9.6;"
            }

            onLinkHovered: {
                curHoverUrl= hoveredUrl
            }
            property string navigateUrl: ""
            property string telNumber: ""
            onNavigationRequested: {
                LOG.logger.verbose("onNavigationRequested request.navigationType: %s", request.navigationType)
            }

            onUrlChanged: {
                LOG.logger.verbose('SWebview onUrlChanged %s',loadProgress)
            }

            onLoadProgressChanged: {
                LOG.logger.verbose('SWebview qml onLoadProgressChanged %s',loadProgress)
                sloadProgress(loadProgress)
            }

            onLoadingChanged: function(loadRequest){
                LOG.logger.verbose('SWebview qml onLoadingChanged status:%s, url:%s', loadRequest.status, loadRequest.url)
                if (loadRequest.status === WebEngineView.LoadFailedStatus){
                    var failedMessage = '[' + loadRequest.errorCode + ']' + loadRequest.errorString;
                    LOG.logger.error('SWebview qml onLoadingChanged LoadFailedStatus: %s, error: %s', loadRequest.url, failedMessage)

                    gToast.requestToast('加载失败: ' + failedMessage);
                }
                if(!loading && loadRequest.status===WebEngineView.LoadSucceededStatus){
                    sloadingChanged(loadRequest);
                }
            }

            onRenderProcessTerminated: function(terminationStatus, exitCode){
                var termMessage = '渲染中断: [' + exitCode + ']';
                switch(terminationStatus){
                    case WebEngineView.NormalTerminationStatus:
                        termMessage += 'NormalTerminationStatus';
                        break;
                    case WebEngineView.AbnormalTerminationStatus:
                        termMessage += 'AbnormalTerminationStatus';
                        break;
                    case WebEngineView.CrashedTerminationStatus:
                        termMessage += 'CrashedTerminationStatus';
                        break;
                    case WebEngineView.KilledTerminationStatus:
                        termMessage += 'KilledTerminationStatus';
                        break;
                }
                reloadTimer.running = true;
                gToast.requestToast(termMessage);
            }

            Timer {
                id: reloadTimer
                interval: 0
                running: false
                repeat: false
                onTriggered: swebview.reload()
            }

             onWindowCloseRequested: function(){
                console.log('onWindowCloseRequested');
                navigationBarClose();
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

            onColorDialogRequested: function(request) {
                request.accepted = true;
            }

            onContextMenuRequested: function(request){
                request.accepted = true;
            }
        }

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

    // 在页面状态变化的时候，处理状态栏展示or隐藏
    onStatusChanged:{
        if(status == CPageStatus.Show){
            console.log('页面展示了！！！', surl)
            pageHide = false
            console.log('gScreenInfo*************', JSON.stringify(gScreenInfo))
            // 跟随屏幕旋转的时候，横屏进入下一个页面，页面状态栏需要手动隐藏，隐藏需2个方法一起使用，才可生效（亲测）
            // 主动被动都需要走这个方法
            if(webView.orientationPolicy == CScreenInfo.Landscape
                || webView.orientationPolicy == CScreenInfo.LandscapeInverted
                || gScreenInfo.currentOrientation == CScreenInfo.Landscape
                || gScreenInfo.currentOrientation == CScreenInfo.LandscapeInverted
            ) {
                webView.statusBarHoldEnabled = false
                gScreenInfo.setStatusBar(false);
            } else {
                console.log('全屏状态===>', projectConfig.statusBarShow())
                //如果为全屏
                if(projectConfig.statusBarShow()){
                    webView.statusBarHoldEnabled = true
                    gScreenInfo.setStatusBar(true);
                    //设置状态栏样式，取值为"black"，"white"，"transwhite"和"transblack"
                    gScreenInfo.setStatusBarStyle(projectConfig.statusBarStyle());
                }else{
                    webView.statusBarHoldEnabled = false
                    gScreenInfo.setStatusBar(false);
                    if(gInputContext.softwareInputPanelVisible) {
                        webView.anchors.bottomMargin = -140
                    } else {
                        webView.anchors.bottomMargin = 0
                    }
                }
            }
        } else if (status == CPageStatus.Hide) {
            console.log('页面将要隐藏啦！！！', surl)
            pageHide = true
        }
    }

    Component.onCompleted: {
        WebEngine.settings.webGLEnabled = true;
        swebview.settings.webGLEnabled = true;

        console.log('gScreenInfo--', JSON.stringify(gScreenInfo))

        // 设置缩放比例
        swebview.zoomFactor = gScreenInfo.density

        console.log('swebview-navigationBarBackgroundColor-', navigationBarBackgroundColor)
        console.log('swebview-navigationBarTitle-', navigationBarTitle)
        console.log('swebview-navigationBarColor-', navigationBarColor)
        console.log('swebview-navigationBarBackIconEnable-', navigationBarBackIconEnable)
        console.log('swebview-navigationBarCloseIconEnable-', navigationBarCloseIconEnable)
        console.log('swebview-backgroundColor-', backgroundColor)

        if (backgroundColor) {
            setBackgroundColor(backgroundColor)
        }

        if (navigationBarTitle) {
            showNavigatorBar({
                navigationBarTitle: navigationBarTitle,
                navigationBarColor: navigationBarColor,
                navigationBarBackgroundColor: navigationBarBackgroundColor,
                navigationBarBackIconEnable: navigationBarBackIconEnable,
                navigationBarCloseIconEnable: navigationBarCloseIconEnable
            })
        }
    }
}