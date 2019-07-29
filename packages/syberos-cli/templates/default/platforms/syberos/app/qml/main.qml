import QtQuick 2.0
import QtWebKit 3.0
import com.syberos.basewidgets 2.0
import QtWebKit.experimental 1.0


CPageStackWindow {
    initialPage:CPage{
        id: root
        width:parent.width
        height:parent.height

        contentAreaItem: Item{


            WebView{
                id: webview
                focus: true
                width: parent.width
                height: parent.height
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                url: "file://" + helper.getWebRootPath() + "/index.html"

                Component.onCompleted: {
                    global.modelMap = {};
                    global.callbackIds = [];
                    global['Download'] = Download;


                    console.log('@@@ completed init modelMap ', JSON.stringify(global.modelMap));
                }

                experimental.preferences.navigatorQtObjectEnabled: true
                experimental.userAgent: "SyberOS"
                experimental.onMessageReceived: {
                    console.log("@@@ ", "WebView received Message: ", message.data, "\r\n")

                    var model = JSON.parse(message.data);

                    var result;
                    if(model.data){
                        var keys = Object.keys(model.data);

                        var funcArgs = [];
                        for(var i in keys){
                            console.log("@@@ ", "key: ", i, keys[i], "\r\n")
                            funcArgs.push((model.data)[keys[i]]);
                        }
                        console.log("@@@ ", "funcArgs: ", funcArgs, "\r\n")
                        result = global['Download'][model.handlerName].apply(null, funcArgs);
                    }else{
                        result = func();
                    }
                    global.modelMap[model.callbackId] = model;
                    global.callbackIds.push(model.callbackId);
                }

                Connections {
                    target: Download
                    onDownloadFailed: {
                        console.log('@@@ onDownloadFailed: ', downloadID, result, errorCode, "\r\n");

                        var callbackId = global.callbackIds.pop();
                        var model = global.modelMap[callbackId];

                        var obj = {
                            responseId: callbackId,
                            responseData: {
                                code: 0,
                                msg:result
                            }
                        }
                        webview.experimental.evaluateJavaScript("JSBridge._handleMessageFromNative(" + JSON.stringify(obj) + ")");
                    }

                    onDownloadCompleted: {
                        console.log('@@@ onDownloadCompleted: ', downloadID, path, "\r\n");
                        var callbackId = global.callbackIds.pop();
                        var model = global.modelMap[callbackId];

                        var obj = {
                            responseId: callbackId,
                            responseData: {
                                result:{
                                    'path': path
                                }

                            }
                        }
                        console.log('@@@ obj:', JSON.stringify(obj), '\r\n');
                        webview.experimental.evaluateJavaScript("JSBridge._handleMessageFromNative(" + JSON.stringify(obj) + ")");
                    }
                }


//                Connections {
//                    target: global
//                    onSuccess: {
//                        var model = global.modelMap[id];
//                        if(model){
//                            delete global.modelMap[id];
//                        }

//                        console.log('@@@ id: ', id, ' json: ', json, ' model: ', JSON.stringify(model));

//                        var resultJSON = JSON.parse(json);
//                        //{
//                        //    id: number,
//                        //    exception: string,
//                        //    result: object
//                        //}
//                        var result = {
//                            'id': id,
//                            'result': resultJSON
//                        }
//                        webview.experimental.postMessage(JSON.stringify(result));
//                    }
//                }

                experimental.alertDialog: CAlertDialog{
                    id: messageDialog
                    canceledOnOutareaClicked: false
                    messageText: model.message
                    onAccepted:{
                        model.accept()
                    }

                    Component.onCompleted:{
                        show()
                    }
                }
            }
        }


    }
}
