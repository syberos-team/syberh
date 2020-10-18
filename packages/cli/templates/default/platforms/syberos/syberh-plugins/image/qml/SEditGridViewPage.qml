/*
 * This file is part of Photos
 * Copyright (C) 2016 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
 * Authors:
 *       Dongshuang Zhao <zhaodongshuang@syberos.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
 */
import QtQuick 2.3
import com.syberos.basewidgets 2.0
// import "./default/CPhotoTranslate"
// import "./default/CPhotoShareDialog"
// import "./default"
import "status.js" as STATUS

/*!
    \qmltype CEditGridViewPage
    \inqmlmodule com.syberos.photos
    \since 2.0
    \ingroup controls
    \brief 图片应用主页

    示例代码:
    \code
    CPageStackWindow {
        initialPage: CEditGridViewPage{
            model: lstModel
        }
        ListModel{id: lstModel}
    }
    \endcode
 */

CPage {
    id: mainPage
    color: gUiConst.getValue("color05")
    statusBarHoldItemColor: gUiConst.getValue("color05")


    /*!
        选中图片的下标数组
    */
    property var arr: []

    /*!
        是否打开编辑状态, 默认开启
    */
    property bool edit: true

    /*!
        \qmlproperty variant CEditGridViewPage::model
        设置视图model的接口，model至少要包含"url"数据项
    */
    property alias model: photoBrowser.model

    /*!
        \qmlproperty bool CEditGridViewPage::editable
        是否可以编辑
    */
    property alias editable: photoBrowser.editable

    /*!
        \qmlproperty bool CEditGridViewPage::editing
        当前是否处于编辑态
    */
    property alias editing: photoBrowser.editing

    /*!
        \qmlproperty int CEditGridViewPage::count
        当前视图中元素的数量
    */
    property alias count: photoBrowser.count

    /*!
        \qmlproperty bool CEditGridViewPage::titleBarActive
        标题栏的有效性
    */
    property bool titleBarActive: true

    /*!
        \qmlproperty QtObject CEditGridViewPage::titleBarItem
        标题栏对象
    */
    property alias titleBarItem: titleBarLoader.item

    /*!
        \qmlproperty bool CEditGridViewPage::toolBarActive
        工具栏的有效性
    */
    property bool toolBarActive: true

    /*!
        \qmlproperty QtObject CEditGridViewPage::toolBarItem
        工具栏对象
    */
    property alias toolBarItem: toolBarLoader.item

    /*!
        \qmlproperty variant CEditGridViewPage::toolButtonNames
        工具栏上按钮的名字，它的值应该是一个数组
    */
//    property variant toolButtonNames: [CPhotoTranslate.share, CPhotoTranslate.del]
    property variant toolButtonNames: ["预览", "确定"]

    /*!
        相册最多选择个数, 默认9张
    */
    property int maxSelectCount: 9

    /*!
        当前点击的是哪个元素
    */
    property int curIndex: -1

    /*!
        \qmlproperty bool CEditGridViewPage::allSelected
        表示是否所有元素都被选中
    */
    readonly property alias allSelected: photoBrowser.allSelected

    /*!
        \qmlproperty int CEditGridViewPage::selectedCount
        表示当前选中的元素的个数，该属性为只读属性。
    */
    readonly property alias selectedCount: photoBrowser.selectedCount

    /*!
        \qmlproperty var CEditGridViewPage::selectedIndexes
        返回当前已选中的元素的index数组。
        \note 返回的数组是按照index值从小到大的顺序排列的。
        如果需要删除model中的数据，请按照index从大到小删除model中的数据。
        以免view刷新导致删除不完全。
    */
    readonly property alias selectedIndexes: photoBrowser.selectedIndexes

    /*! 工具栏上的按钮按下信号，index为按下的按钮的索引值 */
    signal toolButtonClicked(int index)

    /*! 缩略图点击信号，index为缩略图的索引值 */
    signal clicked(int index)

    /*! 预览按钮点击信号，index为缩略图的索引值 */
    signal previewed(int index)

    /*! 确定按钮点击信号，index为缩略图的索引值 */
    signal confirm(var arr)

    /*! 取消按钮点击信号 */
    signal cancel()

    /*!
        \qmlmethod CEditGridViewPage::isSelected(int index)
        判断元素索引为 \a index 的元素是否被选中
    */
    function isSelected(index){
        return photoBrowser.isSelected(index);
    }

    /*!
        \qmlmethod CEditGridViewPage::deselect()
        取消选中所有项目的已选中状态。
    */
    function deselect(){
        photoBrowser.deselect();
    }

    /*!
        \qmlmethod CEditGridViewPage::selectAll()
        选中所有项目。
    */
    function selectAll(){
        photoBrowser.selectAll();
    }

    /*!
        \qmlmethod CEditGridViewPage::select(var indexArray, bool selected)
        用于设置被选中的元素。
        \a indexArray 可以是一个数字，或者是一个数组。
        \a selected 参数用于指定选中状态，它是一个bool值
    */
    function select(indexArray, selected) {
        photoBrowser.select(indexArray, selected);
    }

    /*!
        跳转到预览页面，传model进去
    */
    property QtObject listPreview: null
    function createListPreview(){
        if(!listPreview){
            listPreview = pageStack.getCachedPage(Qt.resolvedUrl("qrc:/qml/SImageListPreview.qml"),
                                                  "SImageListPreviewPage")
            listPreview.model = Qt.binding(function(){return previewModel})
        }
    }

    contentAreaItem: Item{
        SPhotoAndVideoBrowser{
            id: photoBrowser
            anchors.fill: parent
            anchors.topMargin: titleBarLoader.height
            anchors.bottomMargin: toolBarLoader.height
            model: defaultModel

            onClicked: {
                mainPage.curIndex = i
                mainPage.clicked(i)
            }

            enabled: count
        }

        Loader{
            id: titleBarLoader
            width: parent.width
            height: item.height
            active: titleBarActive
            enabled: !photoBrowser.animating
            sourceComponent: SPhotoEditTitleBar{
                editView: photoBrowser
                titleText: CPhotoTranslate.photosAndVideos

                onCanceled: {
                    cancel()
                    pageStack.pop()
                }
            }
        }



        Loader{
            id: toolBarLoader
            width: parent.width
            height: item.height
            anchors.bottom: parent.bottom
            active: toolBarActive
            enabled: !photoBrowser.animating

            sourceComponent: SPhotoToolBar{
                id: photoToolBar
                property QtObject deleteDialogObject: null

                animationVisible: photoBrowser.editing
                onAnimationVisibleChanged:{
                    names = []
                    names = toolButtonNames
                    // 有了按钮区域以后，先吧按钮置灰
                    photoToolBar.enabledIndexes([0,1], false)
                    photoToolBar.lastEnabled = false
                }
                onClicked: {
                    var tmpIndex=0;
                    // 0: 预览 1: 确定
                    if(0 === index) {
                        // 清空lstModel
                        previewModel.clear()

                        // 跳转到预览页面
                        createListPreview()

                        mainPage.selectedIndexes.forEach(function(item) {
                            console.log('----previewModel-url-', model.get(item).url)
                            previewModel.append({ url: model.get(item).url + ''})
                        })

                        mainPage.previewed(mainPage.curIndex)

                        if(listPreview){
                            listPreview.currentIndex = 0
                            pageStack.push(listPreview)
                        }


                    } else if(1 === index) {
                        console.log('确定---', photoBrowser.selectedIndexes)
                        mainPage.confirm(photoBrowser.selectedIndexes)
                        // pageStack.pop()
                    }
                    toolButtonClicked(index)
                }

                property bool lastEnabled: false

                Connections{
                    target: photoBrowser
                    ignoreUnknownSignals: true
                    onSelectedCountChanged:{
                        if(photoBrowser.selectedCount > 0 && !photoToolBar.lastEnabled){
                            photoToolBar.enabledIndexes([0,1], true)
                            photoToolBar.lastEnabled = true
                        }
                        if(photoBrowser.selectedCount <= 0 && photoToolBar.lastEnabled){
                            photoToolBar.enabledIndexes([0,1], false)
                            photoToolBar.lastEnabled = false
                        }
                    }
                }
            }
        }


    }

    SPhotoAndVideoModel{
        id: defaultModel
    }

    SPhotoPreviewModel {
        id: previewModel
    }

    SPhotoAlternate{
        active: mainPage.active && photoBrowser.count === 0 && !defaultModel.busy
    }

    onStatusChanged: {
        if (status === CPageStatus.Show) {
            gScreenInfo.setStatusBar(true)
        }
    }
}
