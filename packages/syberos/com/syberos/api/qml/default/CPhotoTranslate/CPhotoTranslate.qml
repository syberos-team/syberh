/*
 * This file is part of Photos
 * Copyright (C) 2016 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
 * Authors:
 *       Dongshuang Zhao <zhaodongshuang@syberos.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
 */
pragma Singleton
import QtQuick 2.3
import com.syberos.basewidgets 2.0
/*!
    \qmltype
    \inqmlmodule com.syberos.photos
    \since 2.0
    \ingroup controls
    \brief 翻译文件

    示例代码:
    \code
    Text {
        text: CPhotoTranslate.noPhoto
    }
    \endcode
 */

CTranslate {
    path: "/usr/lib/qt5/qml/com/syberos/multimedia/photos/qm"
    name: "photosextension"

//    readonly property string photos: os.i18n.ctr(qsTr("All Photos")) //"所有照片"

    readonly property string photosAndVideos: os.i18n.ctr(qsTr("Photos and Videos")) // "所有照片和视频"

    readonly property string noPhoto: os.i18n.ctr(qsTr("No Photo") ) //"没有照片"

    readonly property string moveOrScale: os.i18n.ctr(qsTr("Move Or Scale") ) //"移动或缩放"

    readonly property string deleteSingle: os.i18n.ctr(qsTr("Sure to delete the selected file?") ) //"确定删除所选的文件吗？"

    readonly property string deleteMultiple: os.i18n.ctr(qsTr("Sure to delete the selected files") ) //"确定删除所选的文件吗？"

    readonly property string deleting: os.i18n.ctr(qsTr("Deleting...","正在删除") )

    readonly property string more:  os.i18n.ctr(qsTr("More") ) //"更多"

    readonly property string cancel: os.i18n.ctr(qsTr("cancel") ) //"取消"

    readonly property string use: os.i18n.ctr(qsTr("use") ) //使用

//    readonly property string confirm: os.i18n.ctr(qsTr("confirm") ) //"确认"

    readonly property string set: os.i18n.ctr(qsTr("Set") ) //"设定"

    readonly property string date: os.i18n.ctr(qsTr("Date: ") ) //"日期: "

    readonly property string format: os.i18n.ctr(qsTr("Format: ") ) //"格式: "

    readonly property string resolution: os.i18n.ctr(qsTr("Resolution: ") ) //"分辨率: "

    readonly property string size: os.i18n.ctr(qsTr("Size: ") ) //"大小: "

//    readonly property string album: os.i18n.ctr(qsTr("album") ) //"相册"

    readonly property string success: os.i18n.ctr(qsTr("set successful") ) //"设置成功"

    readonly property string failed: os.i18n.ctr(qsTr("set failed") ) //"设置失败"

//    readonly property string original: os.i18n.ctr(qsTr("original") ) //"原图"

    readonly property string share: os.i18n.ctr(qsTr("Share"))

    readonly property string del: os.i18n.ctr(qsTr("Delete"))

    readonly property string details: os.i18n.ctr(qsTr("Details"))//"详情"

    readonly property string wallpaper: os.i18n.ctr(qsTr("Set Wallpaper") )//"设置壁纸"

    readonly property string lockScreen: os.i18n.ctr(qsTr("Set Lock Screen"))//"设置锁屏壁纸"

    readonly property string homeScreen: os.i18n.ctr(qsTr("Set Home Screen"))//"设置主屏壁纸"

    readonly property string both: os.i18n.ctr(qsTr("Set Both") )//"设置全部"

    readonly property string sdcardDeleteFailedInfo: os.i18n.ctr(qsTr("sdcard read only", "外置SD卡只读，不能操作外置SD卡") )//"设置全部"

    Component.onCompleted: {
        trans();
    }
}
