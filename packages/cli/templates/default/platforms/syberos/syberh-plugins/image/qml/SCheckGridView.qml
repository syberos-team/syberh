/*
 * This file is part of syberos-toolkit-core
 * Copyright (C) 2016 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
 * Authors:
 *       Dongshuang Zhao <zhaodongshuang@syberos.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
 */
import QtQuick 2.3

GridView {
    id: checkGridView
    objectName: "CCheckGridView_SyberOS2.0"
    interactive: !animating
    maximumFlickVelocity: 2500

    /*! 是否可以编辑*/
    property bool editable:true

    /*! 表示当前的编辑状态，默认值为false，注意：当editing为false时会清除所有项目的选中状态，
        allSelected会被置为false，selectedCount会被置为0， selectedIndexes数组也会被清空。*/
    property bool editing: true

    /*! 表示是否所有元素都被选中*/
    readonly property bool allSelected: count === privateData.selectedCount

    /*!
        \qmlproperty int CCheckGridView::selectedCount
        表示当前选中的元素的个数，该属性为只读属性。
    */
    readonly property int selectedCount: privateData.selectedCount

    /*!
        \qmlproperty var CCheckGridView::selectedIndexes
        返回当前已选中的元素的index数组。
        \note 返回的数组是按照index值从小到大的顺序排列的。
        如果需要删除model中的数据，请按照index从大到小删除model中的数据。
        以免view刷新导致删除不完全。
    */
    readonly property alias selectedIndexes: privateData.selectedIndex

    /*!
        \internal
        \qmlproperty bool CCheckGridView::animating
        只读属性，用于标识视图目前是否正在进行选中和反选动画
    */
    readonly property alias animating: privateData.animating

    /*! 移除动画是否运行 */
    property bool removeAnimationEnabled: true

    /*! 选中动画是否运行 */
    property alias selectAnimationEnabled: privateData.selectAnimationEnabled

    /*! touch控件的对象 */
    property alias mouseArea: mouseAreaObj

    /*! 最大的选择数量 */
//    property int maxSelectCount: 9

    /*! girdview中的元素被按下时发出该信号，参数i表示元素的索引值 */
    signal pressed(int i)

    /*! girdview中的元素被点击时发出该信号，参数i表示元素的索引值 */
    signal clicked(int i)

    /*! girdview中的元素被长按时发出该信号，参数i表示元素的索引值 */
    signal pressAndHold(int i)

    /*! \internal */
    signal indexStatusChanged(int i)

    /*!
        \qmlmethod CCheckGridView::isSelected(int index)
        判断元素索引为 \a index 的元素是否被选中
    */
    function isSelected(index){
        return privateData.indexOf(index) != -1;
    }

    /*!
        \qmlmethod CCheckGridView::deselect()
        取消选中所有项目的已选中状态。
    */
    function deselect(){
        var tmp = contentY
        privateData.selectStart(shownIndexes(), false)
        contentY = tmp // 避免滚动
    }

    /*!
        \qmlmethod CCheckGridView::selectAll()
        选中所有项目。
    */
    function selectAll(){
        if(!allSelected){
            privateData.selectStart(shownIndexes(), true)
        }
    }

    /*!
        \qmlmethod CCheckGridView::select(var indexArray, bool selected)
        用于设置被选中的元素。
        \a indexArray 可以是一个数字，或者是一个数组。
        \a selected 参数用于指定选中状态，它是一个bool值
    */
    function select(indexArray, selected) {
        if(typeof selected === "undefined"){
            selected = true;
        }
        indexArray = indexArray.toString();
        indexArray = indexArray.split(","); // 保证仅输入一个数字，而不是数组也可以正确执行
        if(indexArray.length > 0){
            for(var i=0; i<indexArray.length; ++i){
                if(indexArray[i] >=0 && indexArray[i] < count) {
                    privateData.selectIndex(indexArray[i], selected);
                    var tmp = contentY;
                    currentIndex = indexArray[i];
                    contentY = tmp; // 避免滚动
                }
            }
        }
    }

    /*!
        \qmlmethod CCheckGridView::shownIndexes()
        返回当前显示在视窗中的元素的索引值数组
    */
    function shownIndexes(){
        var idx = [], hash = {}
        if(cellHeight <= 0 || cellWidth <= 0 || 0===count || width <=0 || height <=0){
            return idx
        }
        var elem
        for(var y= contentY - cellHeight/2.0; y < contentY + height + cellHeight/2.0; y+=cellHeight){
            for(var x= contentX - cellWidth/2.0; x < contentX + width + cellWidth/2.0; x+=cellWidth){
                elem = indexAt(x, y)
                if(elem > -1 && !hash[elem]){
                    idx.push(elem)
                    hash[elem] = true
                }
            }
        }
        hash = {}
        return idx
    }

    /*! \internal */
    function __isCurrentShown(index){
        return privateData.itemsWithPos.indexOf(index) !== -1
    }

    onCountChanged: {
        if(editable && editing){
            var tmp = contentY
            privateData.clear();
            contentY = tmp // 避免滚动
        }
    }
    onEditingChanged: {
        var tmp = contentY
        editing ? forceActiveFocus() : privateData.clear()
        contentY = tmp // 避免滚动
    }
//    Keys.onReleased:{
//        if(event.key == Qt.Key_Back || event.key == Qt.Key_Escape) {
//            if(editing){
////                editing = false
//            }
//        }
//    }

    MouseArea {
        id: mouseAreaObj
        anchors.fill: parent
        propagateComposedEvents: true
        enabled: interactive

        function getIndex(mouseX, mouseY){
            return indexAt( contentX + mouseX, contentY + mouseY)
        }

        onPressed: {
            var index = getIndex(mouseX, mouseY)
            if(index > -1){
                checkGridView.pressed(index)
            }
        }

        onClicked: {
            if(!privateData.pressAndHoldFlag){
                var index = getIndex(mouseX, mouseY)
                console.log('--privateData-onClicked--', index, editable && editing)
                if(index > -1){
                    if(editable && editing){
                        var st = !isSelected(index)
                        // 如果是选中效果，并且超过最大选中个数，就return
                        if (privateData.selectedIndex.length >= mainPage.maxSelectCount && st === true) {
                            return
                        }

                        privateData.selectIndex(index, st)
                        indexStatusChanged(index)
                    }
                    checkGridView.clicked(index)
                    mouse.accepted = false
                }
            }else{
                privateData.pressAndHoldFlag = false
            }
        }

        onPressAndHold: {
            privateData.pressAndHoldFlag = true
            var index = getIndex(mouseX, mouseY)
            if(index > -1){
                if(editable && !editing){
                    editing = true
                    privateData.selectIndex(index, true)
                    indexStatusChanged(index)
                }
                checkGridView.pressAndHold(index)
                mouse.accepted = false
            }
        }
    }

    SCheckViewModel{
        id: privateData
        viewCount: count
    }

}
