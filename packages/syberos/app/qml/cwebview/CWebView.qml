

/***************************************************************************
 *
 * Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
 *
 * Authors:
 *       Liu Jingpeng <liujingpeng@syberos.com>
 *       Li Hejia <lihejia@syberos.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
 ****************************************************************************/
import QtQuick 2.5
import QtWebEngine 1.5
import com.syberos.basewidgets 2.0
import "permission.js" as Permission
import "../js/util/log.js" as LOG

/*!
    \qmltype CWebView
    \inqmlmodule com.syberos.webview
    \since 1.0
    \ingroup applicationwindow
    \brief WebView控件

    CWebView是SyberOS基于WebEngieView进行的进一步封装，增强了与SyberOS系统的调用。
    主要功能如下:
    1.默认增加了对FeaturePermission处理机制
    2.增强fileDialogRequested信号对于图片类型是与系统相册与相机的调用
*/
WebEngineView {
    id: webview
    anchors.fill: parent

    /*! 默认对onFeaturePermissionRequested进行处理，如果不需处理，设置为false。 */
    property bool defalutPermission: true
    /*! 是否开启静默授权,默认为false,需手动允许或拒绝。如果为true,则(地理位置获取等)默认允许使用 */
    property bool slienAuth: false
    /*! 是否静默忽略证书错误,默认为false,出现证书错误时弹出确认框。如果为true,则自动确认忽略证书错误 */
    property bool slienCertificateError: false
    /*! 是否开日志打印,默认开启 */
    property bool printLog: false
    //FeaturePermission Object
    property Item permBar: null


    //FeaturePermission信号处理
    onFeaturePermissionRequested: {
        if (defalutPermission) {
            //如果为静默授权
            if (slienAuth) {
                webview.grantFeaturePermission(securityOrigin, feature, true)
                return
            } else {
                permissionAction(securityOrigin, feature)
            }
        }
    }

    //播放视频时,保持亮屏机制
    onRecentlyAudibleChanged: {
        if (recentlyAudible) {
            console.log('[onRecentlyAudibleChanged]  SCREEN_ALWAYS_ON: true, recentlyAudible: ',
                        recentlyAudible)
            gScreenInfo.setWindowProperty("SCREEN_ALWAYS_ON", "true")
        } else {
            console.log('[onRecentlyAudibleChanged]  SCREEN_ALWAYS_ON: false, recentlyAudible: ',
                        recentlyAudible)
            gScreenInfo.setWindowProperty("SCREEN_ALWAYS_ON", "false")
        }
    }

    //打印javascript执行的console
    onJavaScriptConsoleMessage: function(level, message, lineNumber, sourceID){
        switch(level){
        case WebEngineView.InfoMessageLevel:
            LOG.logger.verbose(message)
            break;
        case WebEngineView.WarningMessageLevel:
            LOG.logger.warn(message)
            break;
        case WebEngineView.ErrorMessageLevel:
            LOG.logger.error(message)
            break;
        }
    }

    //弹出alert、confirm、prompt
    onJavaScriptDialogRequested: {
        request.accepted = true;
        showDialog(request);
    }

    //标示文件选择器组件是否已创建
    property bool __fileSelectorCreated: false
    //文件选择器
    onFileDialogRequested: {
        //使用自定义的文件选择器代替默认功能
        request.accepted = true;
        if(__fileSelectorCreated){
           return
        }
        var component = Qt.createComponent("CFileSelector.qml");
        if (component.status === Component.Ready) {
            var componentObj = component.createObject(webview);
            __fileSelectorCreated = true;
            componentObj.selected.connect(function(files){
                console.log('[onFileDialogRequested] selected: ', files);
                request.dialogAccept(files);
                componentObj.destroy();
                __fileSelectorCreated = false;
            })
            componentObj.cancelled.connect(function(){
                console.log('[onFileDialogRequested] cancelled');
                request.dialogReject();
                componentObj.destroy();
                __fileSelectorCreated = false;
            });
            componentObj.show();
        }else{
            console.log('[onFileDialogRequested] failed:', component.errorString())
        }
    }

    // 证书错误
    onCertificateError: function(certErr){
        console.log('[onCertificateError]:', certErr.url, certErr.description, certErr.error, certErr.overridable);
        if(slienCertificateError){
            certErr.ignoreCertificateError();
            return;
        }

        certErr.defer();

        showDialog({
            type: JavaScriptDialogRequest.DialogTypeConfirm,
            message: '证书错误: \n' + certErr.description + '\n' + certErr.url,
            acceptedButtonText: '继续',
            rejectButtonText: '取消',
            dialogAccept: certErr.ignoreCertificateError,
            dialogReject: certErr.rejectCertificate
        })
    }


    //处理Permission请求
    function permissionAction(securityOrigin, feature) {
        var action = Permission.getPermission(securityOrigin, feature)
        if (action == null) {
            if (!permBar) {
                //动态创建
                var cmp = Qt.createComponent("FeaturePermission.qml")
                if (cmp.status === Component.Error) {
                    console.error(
                                "CWebView.qml create FeatruePermission error:",
                                cmp.errorString())
                }
                if (cmp.status === Component.Ready) {
                    permBar = cmp.createObject(webview, {
                                                   "securityOrigin": securityOrigin,
                                                   "requestedFeature": feature,
                                                   "view": webview
                                               })
                    console.assert(permBar)
                    permBar.show()
                    permBar.onAccepted.connect(function () {
                        permBar.destroy();
                        permBar = null;
                    })
                }
            } else {
                permBar.securityOrigin = securityOrigin;
                permBar.requestedFeature = feature;
                permBar.show()
            }
        } else {
            webview.grantFeaturePermission(securityOrigin, feature, action)
        }
    }

    /**
     * alert、confirm、prompt弹出框
     * 参数 request:
     *    type                  弹出框类型：DialogTypeAlert, DialogTypeConfirm, DialogTypePrompt
     *    message               消息内容文本
     *    defaultText           默认的值，仅适用于 DialogTypePrompt
     *    acceptedButtonText    确认按钮文本
     *    rejectButtonText      取消按钮文本
     *    dialogAccept          确认回调函数，仅 DialogTypePrompt时有参数text，表示输入的值
     *    dialogReject          取消回调函数
     */
    function showDialog(request) {
        if(!request){
            console.log('[showDialog] failed: request is null');
            return;
        }
        var properties = {'text': request.message};
        var qml;
        switch(request.type){
        case JavaScriptDialogRequest.DialogTypeAlert:
            qml = Qt.resolvedUrl("AlertDialog.qml");
            if(request.acceptedButtonText){
                properties.alertButtonText = request.acceptedButtonText;
            }
            break;
        case JavaScriptDialogRequest.DialogTypeConfirm:
            qml = Qt.resolvedUrl("ConfirmDialog.qml");
            if(request.acceptedButtonText){
                properties.acceptedButtonText = request.acceptedButtonText;
            }
            if(request.rejectButtonText){
                properties.rejectButtonText = request.rejectButtonText;
            }
            break;
        case JavaScriptDialogRequest.DialogTypePrompt:
            qml = Qt.resolvedUrl("PromptDialog.qml");
            if(request.acceptedButtonText){
                properties.acceptedButtonText = request.acceptedButtonText;
            }
            if(request.rejectButtonText){
                properties.rejectButtonText = request.rejectButtonText;
            }
            break;
        }
        if(!qml){
            console.log('[showDialog] failed: request.type invalid', request.type);
            return;
        }
        var component = Qt.createComponent(qml);
        if (component.status !== Component.Ready) {
            console.log('[showDialog] failed:', component.errorString());
            return;
        }
        var componentObj = component.createObject(webview, properties);
        componentObj.rejected.connect(function(){
            request.dialogReject();
            componentObj.destroy();
        });
        if(request.type === JavaScriptDialogRequest.DialogTypePrompt){
            if(request.defaultText){
                componentObj.setText(request.defaultText);
            }
            componentObj.inputAccepted.connect(function(text){
                request.dialogAccept(text);
                componentObj.destroy();
            });
        }else{
            componentObj.accepted.connect(function(){
                request.dialogAccept();
                componentObj.destroy();
            });
        }
        componentObj.show();
    }
}
