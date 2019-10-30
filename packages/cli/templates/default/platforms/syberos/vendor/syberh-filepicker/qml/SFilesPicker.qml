/*
* This file is part of syberh
*
* Copyright (C) 2019 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*       Xue Jun <zhanghuanlin@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

import QtQuick 2.0
import com.syberos.basewidgets 2.0
import org.nemomobile.thumbnailer 1.0
import com.syberos.filemanager.filepicker 1.0

CPage {
    id: filesPicker
    statusBarHoldEnabled: true
    statusBarHoldItemColor: "white"
    orientationLock: CPageOrientation.LockPortrait
    clip: true

    property string titleText: "" // 标题文字
    property string categoryType: "all" // 接收页面参数转化为category 0: all, 1: image, 2: video, 3: audio, 4: document, 5: text
    property bool leftItemEnabled: false  // 是否展示左侧icon

    property var filesPath //for email
    property int category: 4 //0: all, 1: image, 2: video, 3: audio, 4: document, 5: text
    property var dirPath //for download

    property bool isDirMode: false

    // 多选的最大数量
    property int count: 1

    signal cancel()
    signal ok(var filesPath)

    function getFileSize() {
        if (category === 0)
            return typeModel.getSelectedFilesSize();
        else
            return galleryModel.getSelectedFilesSize();
    }

    function getDirPath() {
        return typeModel.path;
    }

    TypeModel {
        id: typeModel
    }

    GalleryModel {
        id: galleryModel
    }

    Utils {
        id: fileUtils
    }

    contentAreaItem: SFilesPickerView {
        id: filesView
        titleText: filesPicker.titleText
        leftItemEnabled: filesPicker.leftItemEnabled
    }

    onStatusChanged: {
        // 状态从1到2， 才接收到了参数, 打印日志发现的
        if (status === 2) {
            if (categoryType === "all") {
                category = 0
            } else if (categoryType === "image") {
                category = 1
            } else if (categoryType === "video") {
                category = 2
            } else if (categoryType === "audio") {
                category = 3
            } else if (categoryType === "document") {
                category = 4
            } else if (categoryType === "text") {
                category = 5
            } else {
                category = 0
            }


            switch(category) {
                case 0:
                    typeModel.path = "";
                    filesView.focus = true
                    break;
                case 1:
                    galleryModel.rootType = "Image";
                    break;
                case 2:
                    galleryModel.rootType = "Video";
                    break;
                case 3:
                    galleryModel.rootType = "Audio";
                    break;
                case 4:
                    galleryModel.rootType = "Document";
                    break;
                case 5:
                    galleryModel.rootType = "Text";
                    break;
                default:
                    break;
            }
        }
    } //end onStatusChanged
} //end
