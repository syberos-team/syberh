import QtQuick 2.0
import QtQml.Models 2.2
import com.syberos.basewidgets 2.0

/*!
    \qmltype CFileSelector
    \inqmlmodule com.syberos.webview
    \since 1.0
    \ingroup controls
    \brief 文件选择弹出框

    CFileSelector 提供3种选项："拍照"、"照片图库"、"浏览"。
    拍照：唤起相机拍照，完成后 selected 信号中提供照片路径。
    照片图库：调用相册，选择图片或视频，完成后 selected 信号中提供照片或视频路径。
    浏览：调用文件选择器，完成后 selected 信号中提供文件路径。

    CFileSelector 使用 cameraEnabled、albumEnabled、filePickerEnabled 控制启用或停用上面3种中的一种或多种，但最少需要保证一个选项是启用的。

    由于 CFileSelector 是使用的 CListDialog 组件，在使用是需要调用 show() 函数显示弹出框。调用 show() 函数后会切换至对应的选择页面。

    当用户触摸其中一个选项时，会触发对应的信号，分别是：cameraTriggered、albumTriggered、filePickerTriggered。

    示例代码:
    \qml
    property bool __fileSelectorCreated: false
    onFileDialogRequested: {
        //使用自定义的文件选择器代替默认功能
        request.accepted = true;
        console.log('#### onClicked')
        if(__fileSelectorCreated){
            console.log('+++++++++++++++ fileSelectorCreated')
           return
        }
        var component = Qt.createComponent(Qt.resolvedUrl("CFileSelector.qml"));
        if (component.status === Component.Ready) {
            var componentObj = component.createObject(webview);
            __fileSelectorCreated = true;
            componentObj.cameraTriggered.connect(function(){
                console.log('>>>>>>> cameraTriggered')
            });
            componentObj.albumTriggered.connect(function(){
                console.log('>>>>>>> albumTriggered')
            });
            componentObj.filePickerTriggered.connect(function(){
                console.log('>>>>>>> albumTriggered')
            });
            componentObj.selected.connect(function(files){
                console.log('>>>>>>> selected: ', files)
                componentObj.destroy();
                __fileSelectorCreated = false;
            })
            componentObj.cancelled.connect(function(){
                console.log('>>>>>>> cancelled')
                componentObj.destroy();
                __fileSelectorCreated = false;
            });
            componentObj.show();
        }else{
            console.log(component.errorString())
        }
    }
    \endqml
*/
CListDialog {
    id: dialog

    /*!
        \qmlproperty bool CListDialog::cameraEnabled
        是否启用拍照选项，默认为启用
     */
    property bool cameraEnabled: true
    /*!
        \qmlproperty bool CListDialog::albumEnabled
        是否启用照片图库选项，默认为启用
     */
    property bool albumEnabled: true
    /*!
        \qmlproperty bool CListDialog::filePickerEnabled
        是否启用浏览选项，默认为启用
     */
    property bool filePickerEnabled: true
    /*!
        \qmlproperty bool CListDialog::selectMultiple
        是否可多选，默认为false
        尚未实现，目前根据各个公共组件的默认行为决定是否能够多选。拍照便是单选，照片图库是多选，浏览是多选。
     */
    property bool selectMultiple: false
    /*!
        \qmlproperty var CListDialog::nameFilters
        调用文件选择器是，可选择的文件类型，使用HTML中input file元素的accept属性，见：https://developer.mozilla.org/zh-CN/docs/Web/HTML/Element/input/file#attr-accept
        尚未实现，目前选择所有类型的文件
     */
    property var nameFilters

    /*!
        触摸拍照选项时触发的信号
     */
    signal cameraTriggered()
    /*!
        触摸照片图库选项时触发的信号
     */
    signal albumTriggered()
    /*!
        触摸浏览选项时触发的信号
     */
    signal filePickerTriggered()
    /*!
        选择文件后触发的信号，根据不同的选项触发的时机也不相同。
        拍照：拍照完成并确认后触发
        照片图库：选择完图片并确认后触发
        浏览：选择文件并确定后触发
        \a files 是一个数组类型，其中每一项是一个选中文件的路径
     */
    signal selected(var files)
    /*!
        取消选择，从选择页面返回是触发
     */
    signal cancelled()

    /* 提供选择的选项 */
    readonly property var contentList: ["拍照", "照片图库", "浏览"]

    buttonAreaEnabled: false
    itemCheckable: false

    /* 当触摸弹出框外部时，弹出框隐藏并触发 cancelled 信号 */
    onHideFinished: {
        if(dialog.selectedCount() < 1){
            cancelled()
        }
    }

    onDelegateItemTriggered: {
        var modelContent = (dialog.model)[index];
        var contentIndex = contentList.indexOf(modelContent);
        if(contentIndex < 0){
            return
        }
        dialog.triggerAction(contentIndex);
    }

    /* 根据选项开关，向CListDialog中的model添加数据 */
    Component.onCompleted: {
        var modelData = [];
        if(cameraEnabled){
            modelData.push(contentList[0]);
        }
        if(albumEnabled){
            modelData.push(contentList[1]);
        }
        if(filePickerEnabled){
            modelData.push(contentList[2]);
        }
        dialog.model = modelData;
    }

    /* 根据选中的选项调用对应的功能，\a contentIndex 对应 contentList 中的下标 */
    function triggerAction(contentIndex){
        switch(contentIndex){
        case 0:
            dialog.cameraTriggered()
            if(dialog.cameraEnabled){
                openCamera();
            }
            break;
        case 1:
            dialog.albumTriggered()
            if(dialog.albumEnabled){
                openAlbum();
            }
            break;
        case 2:
            dialog.filePickerTriggered()
            if(dialog.filePickerEnabled){
                openFilePicker();
            }
            break;
        }
    }

    function openCamera(){
        var cameraPage = pageStack.push("qrc:/qml/cwebview/CameraPage.qml", {'parentItem': dialog.parent});
        cameraPage.confirmed.connect(function(filePath, isFullImage){
            dialog.selected([filePath]);
        });
        cameraPage.cancelled.connect(function(){
            dialog.cancelled();
        });
    }

    function openAlbum(){
        var albumPage = pageStack.push("qrc:/qml/cwebview/AlbumPage.qml",
                                       {'parentItem': dialog.parent, 'toolButtonNames': ["确定"]});
        albumPage.selected.connect(function(files){
            gToast.requestToast(files);
            dialog.selected(files);
        });
        albumPage.cancelled.connect(function(){
            dialog.cancelled();
        })
    }

    function openFilePicker(){
        var filePickerPage = pageStack.push("qrc:/qml/cwebview/FilePickerPage.qml",
                                            {'selectMultiple': selectMultiple, 'nameFilters': nameFilters});
        filePickerPage.ok.connect(function(){
            dialog.selected(filePickerPage.filesPath);
        });
        filePickerPage.cancel.connect(function(){
            dialog.cancelled();
        });
    }
}
