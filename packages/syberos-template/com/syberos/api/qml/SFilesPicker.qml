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

    property var filesPath //for email
    property string category: "all" //all, image, video, audio, document, file, text, album, folder, photoAlbum, albumArtist
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
        console.log("-------------filePicker: dir path:", typeModel.path);
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
    }

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            switch(category) {
            case "all":
                typeModel.path = "";
                filesView.focus = true
                break;
            case "image":
                galleryModel.rootType = "Image";
                break;
            case "video":
                galleryModel.rootType = "Video";
                break;
            case "audio":
                galleryModel.rootType = "Audio";
                break;
            case "document":
                galleryModel.rootType = "Document";
                break;
            case "file":
                galleryModel.rootType = "File";
                break;
            case "text":
                galleryModel.rootType = "Text";
                break;
            case "album":
                galleryModel.rootType = "Album";
                break;
            case "folder":
                galleryModel.rootType = "Folder";
                break;
            case "photoAlbum":
                galleryModel.rootType = "PhotoAlbum";
                break;
            case "albumArtist":
                galleryModel.rootType = "AlbumArtist";
                break;
            default:
                break;
            }
        }
    } //end onStatusChanged
} //end
