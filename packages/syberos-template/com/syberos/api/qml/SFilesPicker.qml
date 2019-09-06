/*
* This file is part of clock
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
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
    property bool leftItemEnabled: false  // 是否展示左侧icon

    property var filesPath //for email
    property int category: 0 //0: all, 1: image, 2: video, 3: audio, 4: document, 5: text, 6: album, 7: photoAlbum
    property var dirPath //for download

    property bool isDirMode: false

    signal cancel()
    signal ok(var path)

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
        if (status === CPageStatus.WillShow) {
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
                case 6:
                    galleryModel.rootType = "Album";
                    break;
                case 7:
                    galleryModel.rootType = "PhotoAlbum";
                    break;
            default:
                break;
            }
        }
    } //end onStatusChanged
} //end
