import QtQuick 2.0
import QtWebKit 3.0
import com.syberos.basewidgets 2.0
import QtWebKit.experimental 1.0
import	QtMultimedia	5.0
import com.syberos.download 1.0
CPageStackWindow {
    initialPage:CPage{
        id: root
        width:parent.width
        height:parent.height
        Component.onCompleted: {
            /// 通过获取Object的方式访问对象导出的接口
          var status =  NativeSdkManager.getUiSource("CameraHandler*","").getCameraFlashMode();
        }

        contentAreaItem: Item{
            WebView{
                id: webview
                focus: true
                width: parent.width
                height: 500
                anchors.top: parent.top

                url: "file://" + helper.getWebRootPath() + "/index.html"

                experimental.preferences.navigatorQtObjectEnabled: true
                experimental.userAgent: "SyberOS"
                experimental.onMessageReceived: {
                    console.log("@@@ ", "WebView received Message: ", message.data, "\r\n")
                    var model = JSON.parse(message.data);
                    var result;
                    if(model.data){
                        var keys = Object.keys(model.data);

                        var funcArgs = {};
                        for(var i in keys){
                            console.log("@@@ ", "key: ", i, keys[i], "\r\n")
                            console.log("@@@ value is",model.data[keys[i]]);
                            funcArgs[keys[i]] = model.data[keys[i]];
                        }

                        NativeSdkManager.request("TestHandler*",model.callbackId,model.handlerName,funcArgs);
                    }

                }
                Connections{
                    target: NativeSdkManager
                    onSucess:{
                        console.log("request sucess " +result);
                        gToast.requestToast("request sucess " +result);
                    }
                    onFailed:{
                        gToast.requestToast("request failed " + errorMsg);
                        console.log("request failed " + errorMsg);
                        var callbackId = responseID;
                        var obj = {
                            responseId: callbackId,
                            responseData: {
                                code: 0,
                                msg:errorMsg
                            }
                        }
                        webview.experimental.evaluateJavaScript("JSBridge._handleMessageFromNative(" + JSON.stringify(obj) + ")");
                    }
                }
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
             //静态布局
            Test{
                id:staticQml
                anchors.top: webview.bottom
                height:200
                Component.onCompleted: {
                 console.log(RelativeTime.timeSince(new Date()) + " ago");
                }
            }
            /// 动态布局 c++中加载qml
            Item{
                id:item
                objectName:"objItem"
                width: parent.width
                height: 200
                anchors.top :staticQml.bottom
                anchors.topMargin: 10
                Component.onCompleted: {
                    timer.start()
                 }
            }
            Timer{
                id:timer
                interval: 10
                repeat: false
                onTriggered:NativeSdkManager.loadQml("LoadQmlHandler*","","objItem","")
            }

        }


    }
}
