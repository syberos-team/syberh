import QtQuick 2.3
import com.syberos.basewidgets 2.0

CListDialog{
    id: selectedDialog
    property var sourceType:['camera', 'album']
    signal receiveUrls(var urls)
    property int count:9
    titleText: "选择图片"
    onNotifySelectedItems: {
        console.log("choice indexes ======> ", itemsIndex)
        toPage(itemsIndex[0])
    }

//    function show(){
//        if (sourceType === ['album']) {
//            // 弹出框
//            var obj= PageStack.push("qrc:/com/syberos/api/qml/SEditGridViewPage.qml")
//            obj.confirm.connect(function(arr){
//                console.log('九宫格页面---' , arr)
//                selectedDialog.receiveUrls(arr)
//            })

//        } else if (sourceType === ['camera']) {

//        }
//    }

    function toPage(idx) {
        console.log('toPage toPage toPage', selectedDialog.count)
        if (idx === 0) {
            var imageComponent= pageStack.push("qrc:/com/syberos/api/qml/SEditGridViewPage.qml")

            imageComponent.maxSelectCount = selectedDialog.count || 9

            // 用户点击确定按钮
            imageComponent.confirm.connect(function(arr){
                console.log('九宫格页面---' , arr)
                selectedDialog.receiveUrls(arr)
            })

            // 用户点击取消按钮
            imageComponent.cancel.connect(function() {
                console.log('监听到---取消按钮')
                WEBVIEWCORE.trigger('success', that.handlerId)
            })
        } else if (idx === 1) {
            var cameraComponent= pageStack.push("qrc:/com/syberos/api/qml/SCamera.qml")

            cameraComponent.imageConfirmed.connect(function(filePath) { //处理信号
                console.log('-------------------------------------takePictureImmediately', filePath)
                pageStack.pop(root)
                filePath = "file://"+filePath;
                var arr = [{ path: filePath }]
                selectedDialog.receiveUrls(arr)
            })
        }
    }

//    function transformSourceType(arr) {
//        var newArr = []
//        var obj = {'camera': '拍照', 'album': '从手机相册选择'}
//        arr.forEach(function(item) {
//            newArr.push(obj(item))
//        })
//        return newArr
//    }


    Component.onCompleted: {
        model = selectedDialog.sourceType
        select([0],true);
    }
}
