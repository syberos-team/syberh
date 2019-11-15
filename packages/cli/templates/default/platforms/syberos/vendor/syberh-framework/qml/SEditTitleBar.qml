/*
 * This file is part of syberos-toolkit-core
 * Copyright (C) 2015 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
 * Authors:
 *       Dongshuang Zhao <zhaodongshuang@syberos.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
 */

import QtQuick 2.3
import "../items"

/*!
    \qmltype CEditTitleBar
    \inqmlmodule com.syberos.basewidgets
    \since 2.0
    \ingroup controls
    \inherits CTitleBar
    \brief 带有编辑状态的标题栏

    与CEditListView或CEditGridViewd配合使用，完成编辑行为。
    有编辑态和非编辑态两种状态，处于非编辑态时，外观为普通CTitleBar；处于编辑态时，左侧为取消功能，右侧为全选/取消全选功能。

    示例代码及外观见 \l {com.syberos.basewidgets::CEditListView}{CEditListView}
    或 \l {com.syberos.basewidgets::CEditGridView}{CEditGridView}
*/

CTitleBar{
    id:ceditTitleBar
    objectName: "CEditTitleBar_SyberOS2.0"
    spacingBetweenRightBorderAndRightItem: editing?20:(rightItemBackgroundEnabled?20:0)
    clip: true // 防止动画越界

    /*! 标识动画是否正在进行，只读属性。*/
    readonly property bool animating: toEditAnimation.running || toNomalAnimation.running

    /*!  titleBar需要编辑的视图对象，该视图对象需要具有布尔类型的editing属性 */
    property Item editView:null

    onEditViewChanged: {
        if(editView) {
            if (typeof ceditTitleBar.editRightItem != "undefined" && ceditTitleBar.editRightItem != null){
                ceditTitleBar.editRightItem.checked = editView.allSelected
            }
        }
    }

    Connections{
        target:editView
        ignoreUnknownSignals: true
        onAllSelectedChanged:{
            ceditTitleBar.editRightItem.checked = editView.allSelected
        }
        onSelectedCountChanged:{
            if(editView.editing){
                editTitleItemLoader.selectedCount = editView.selectedCount
            }
        }
    }

    /*! 默认左侧按钮在编辑态被点击时发出该信号，如果定制了左侧按钮则不会发出。*/
    signal canceled()

    /*! 默认右侧按钮在编辑态被点击，并且没有指定editView属性时发出该信号。*/
    signal editAllTriggered(bool checked)

    /*! 当前是否处于编辑态。 */
    property bool editing:  editView  ? editView.editing : false

    /*! 编辑态时左侧控件文字。 */
    property string editLeftItemText:os.i18n.ctr(qsTr("Cancel"))

    /*! 编辑态时左侧控件文字颜色。 */
    property color editLeftItemTextColor:gUiConst.getValue("CT1")

    /*! 编辑态时左侧控件文字大小。 */
    property int editLeftItemPixelSize: env.dp(gUiConst.getValue("S3"))

    /*! 编辑态时左侧控件背景是否启用，默认为true。 */
    property bool editLeftItemBackgroundEnabled:true

    /*!
        \qmlproperty Component CEditTitleBar::editLeftComponent
        编辑态时左侧组件，默认为取消按钮，可定制。
    */
    property alias editLeftComponent:editLeftItemLoader.sourceComponent

    /*!
        \qmlproperty object CEditTitleBar::editLeftItem
        编辑态时左侧控件Item
    */
    property alias editLeftItem:editLeftItemLoader.item

    /*!  编辑态时左侧控件的size，默认值为120×56 */
    property size editLeftItemSize: Qt.size(env.dp(120),env.dp(56))

    /*!  编辑态时左侧控件距离左侧边缘的距离 */
    property int editLeftItemLeftMargin: env.dp(40)

    Loader{
        id:editLeftItemLoader
        anchors.verticalCenterOffset: parent.verticalOffset
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: editLeftItemLeftMargin
        width:editLeftItemSize.width
        height:editLeftItemSize.height
        sourceComponent: CButton{
            text:editLeftItemText
            textColor:editLeftItemTextColor
            pixelSize: editLeftItemPixelSize
            backgroundEnabled: editLeftItemBackgroundEnabled
            onClicked: {
                if(editView)
                {
                    editView.editing = false
                    editView.deselect()
                }
                else
                    ceditTitleBar.canceled()
            }
        }
        visible: false
    }

    /*!  编辑态时标题控件文字大小 */
    property int editTitlePixelSize: titlePixelSize

    /*!  编辑态时标题控件文字颜色 */
    property color editTitleTextColor: titleTextColor

    /*! 编辑态时标题控件文字 */
    property string editTitleText:{
        if(editView){
            return os.i18n.ctr(qsTr("Selected ")) +editTitleItemLoader.selectedCount + os.i18n.ctr(qsTr(" item(s)"))
        }else{
            return os.i18n.ctr(qsTr("Selected 0 item"))
        }
    }

    /*!
        \qmlproperty Component CEditTitleBar::editTitleComponent
        编辑态时标题区域组件，默认为Text，可定制。
    */
    property alias editTitleComponent:editTitleItemLoader.sourceComponent

    /*!
        \qmlproperty object CEditTitleBar::editTitleItem
        编辑态时标题控件对象
    */
    property alias editTitleItem:editTitleItemLoader.item

    Loader{
        id:editTitleItemLoader
        property int selectedCount: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: parent.verticalOffset
        anchors.horizontalCenter: parent.horizontalCenter
        sourceComponent: Text{
            color:editTitleTextColor
            font.pixelSize: editTitlePixelSize
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text:editTitleText
        }
        visible: false
    }

    /*!
        \qmlproperty Component CEditTitleBar::editRightComponent
        编辑态时右侧区域组件，默认为CCheckBox，可定制。
    */
    property alias editRightComponent:editRightItemLoader.sourceComponent

    /*!
        \qmlproperty object CEditTitleBar::editRightItem
        编辑态时右侧控件对象
    */
    property alias editRightItem:editRightItemLoader.item

    /*!  编辑态时右侧控件的size值，默认为80×56 */
    property size editRightItemSize:Qt.size(env.dp(80),env.dp(56))

    /*!  编辑态时右侧控件距离右侧边缘的距离 */
    property int editRightItemRightMargin: env.dp(20)

    /*! 按下状态的颜色。 */
    property color editRightItemCheckedColor: gUiConst.getValue("CA1")

    /*! 非按下状态的颜色。 */
    property color editRightItemNormalColor: gUiConst.getValue("CI1")

    Loader{
        id:editRightItemLoader
        anchors.verticalCenterOffset: parent.verticalOffset
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: editRightItemRightMargin//spacingBetweenRightBorderAndRightItem// - (((typeof editRightItem.width != "undefined") && editRightItem.width > 0) ? 0 : 10)
        width: env.dp(editRightItemSize.width)
        height: env.dp(editRightItemSize.height)
        sourceComponent:  Item{} /*CCheckBox{
            checked: editView ? editView.allSelected : false
            enabled: editView ? (!editView.animating) : true
            checkedColor: editRightItemCheckedColor
            normalColor: editRightItemNormalColor
            onClicked: {
                if(editView) {
                    checked ? editView.selectAll() : editView.deselect()
                } else {
                    ceditTitleBar.editAllTriggered(checked)
                }
            }
        }*/
        visible: false
    }

    onEditingChanged: {
        if(editing)
            toEditAnimation.restart()
        else
            toNomalAnimation.restart()
    }
    ParallelAnimation{
        id:toEditAnimation
        SequentialAnimation{
            ScriptAction{
                script: {
                    editLeftItemLoader.anchors.leftMargin = -editLeftItemLoader.width-10
                    editLeftItemLoader.visible = true
                }
            }
            NumberAnimation{
                target: leftItemEnabled && leftItem?leftItem.parent:null
                property:"anchors.leftMargin"
                to:leftItemEnabled?-leftItem.parent.width-10:0
                duration: gSystemUtils.durationRatio*150
                easing.type: Easing.OutCubic
            }
            NumberAnimation{
                target:editLeftItemLoader
                property:"anchors.leftMargin"
                to:editLeftItemLeftMargin
                duration: gSystemUtils.durationRatio*150
                easing.type: Easing.OutCubic
            }
        }
        SequentialAnimation{
            ScriptAction{
                script: {
                    if(titleItemEnabled && titleItem){
                        titleItem.parent.opacity = 0
                    }
                    editTitleItemLoader.opacity = 0
                    editTitleItemLoader.visible = true
                }
            }
            OpacityAnimator{
                target:editTitleItemLoader
                from: 0.0
                to: 1.0
                duration: gSystemUtils.durationRatio*300
            }
        }
        SequentialAnimation{
            ScriptAction{
                script: {
                    editRightItemLoader.scale = 0
                    editRightItemLoader.visible = true
                }
            }
            ScaleAnimator{
                target: rightItemEnabled && rightItem?rightItem.parent:null
                from: 1.0
                to:0.0
                duration: gSystemUtils.durationRatio*200
            }
            ScaleAnimator{
                target:editRightItemLoader
                from: 0.0
                to:1.0
                duration: gSystemUtils.durationRatio*200
            }
        }
        onStopped: {
            if(leftItem) {
                leftItem.parent.visible = false
            }
            if(titleItem) {
                titleItem.parent.visible = false
            }
            if(rightItem) {
                rightItem.parent.visible = false
            }
        }
    }

    ParallelAnimation{
        id:toNomalAnimation
        SequentialAnimation{
            ScriptAction{
                script: {
                    if(leftItem && leftItemEnabled) {
                        leftItem.parent.anchors.leftMargin = -leftItem.parent.width
                        leftItem.parent.visible = true
                    }
                }
            }

            NumberAnimation{
                target:editLeftItemLoader
                property:"anchors.leftMargin"
                to:-editLeftItemLoader.width - editLeftItemLeftMargin
                duration: gSystemUtils.durationRatio*150
                easing.type: Easing.OutCubic
            }
            NumberAnimation{
                target:leftItemEnabled && leftItem?leftItem.parent:null
                property:"anchors.leftMargin"
                to: spacingBetweenLeftBorderAndLeftItem
                duration: gSystemUtils.durationRatio*150
                easing.type: Easing.OutCubic
            }
        }
        SequentialAnimation{
            ScriptAction{
                script: {
                    if(titleItem){
                        titleItem.parent.opacity = 0
                        titleItem.parent.visible = true
                        editTitleItemLoader.opacity = 0
                    }
                }
            }
            OpacityAnimator{
                target: titleItem?titleItem.parent:null
                from: 0.0
                to:1.0
                duration: gSystemUtils.durationRatio*300
            }
        }
        SequentialAnimation{
            ScriptAction{
                script: {
                    if(rightItemEnabled && rightItem) {
                        rightItem.parent.scale = 0
                        rightItem.parent.visible = true
                    }
                }
            }
            ScaleAnimator{
                target:editRightItemLoader
                from: 1.0
                to: 0.0
                duration: gSystemUtils.durationRatio*200
            }
            ScaleAnimator{
                target:rightItemEnabled && rightItem?rightItem.parent:null
                from: 0.0
                to: 1.0
                duration: gSystemUtils.durationRatio*200
            }
        }

        onStopped: {
            if(editLeftItemLoader.active) {
                editLeftItemLoader.visible = false
            }
            if(editTitleItemLoader.active) {
                editTitleItemLoader.visible = false
            }
            if(editRightItemLoader.active) {
                editRightItemLoader.visible = false
            }
        }
    }

    flickableObject: editView
}

