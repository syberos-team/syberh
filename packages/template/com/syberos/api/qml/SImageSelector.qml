import QtQuick 2.3
import com.syberos.basewidgets 2.0

CListDialog{
    id: selectedDialog
    signal receiveUrls(var urls)
    property int count:9
    titleText: "选择图片"
    buttonAreaComponent: null

    onDelegateItemTriggered: {
        toPage(index)
    }

    function toPage(idx) {
        if (model[idx] === "从手机相册选择") {
            var imageComponent= pageStack.push("qrc:/com/syberos/api/qml/SEditGridViewPage.qml")

            imageComponent.maxSelectCount = selectedDialog.count || 9

            // 用户点击确定按钮
            imageComponent.confirm.connect(function(arr){
                var newArr = []
                arr.forEach(function(item) {
                    newArr.push({
                        path: imageComponent.model.get(item).url + '',
                        size: imageComponent.model.get(item).fileSize
                    })
                })
                selectedDialog.receiveUrls(newArr)
            })

            // 用户点击取消按钮
            imageComponent.cancel.connect(function() {
                console.log('监听到---取消按钮')
            })
        } else if (model[idx] === "相机") {
            var cameraComponent= pageStack.push("qrc:/com/syberos/api/qml/SCamera.qml")

            cameraComponent.imageConfirmed.connect(function(filePath) {
                pageStack.pop(root)
                var size = fileutil.getInfoSize(filePath)
                filePath = "file://"+filePath;
                var arr = [{ path: filePath, size: size }]
                selectedDialog.receiveUrls(arr)
            })
        }
    }

    function open(obj){
        selectedDialog.count = Number(obj.count)
        model = transformType(eval(obj.sourceType))
        selectedDialog.show()
    }

    function transformType(arr) {
        var newArr = []
        for (var i=0; i < arr.length; i++) {
            var item = arr[i]
            if (item === 'camera') {
                newArr.push('相机')
            } else if (item === 'album') {
                newArr.push('从手机相册选择')
            }
        }
        return newArr
    }

}
