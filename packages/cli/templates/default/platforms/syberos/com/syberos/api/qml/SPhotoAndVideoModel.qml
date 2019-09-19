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
import QtDocGallery 5.0

/*!
\qmltype CPhotoAndVideoModel
\inqmlmodule com.syberos.photos
\since 2.0
\ingroup controls
\brief 该控件用于同时获取图片和视频
*/

DocumentGalleryModel {
    id: pModel
    autoUpdate: true
    sortProperties: ["-lastModified"]
    properties: [ "url", "mimeType", "width", "height", "fileSize"]
    rootType: DocumentGallery.Visual
    filter: GalleryFilterUnion {
        filters:[
            GalleryContainsFilter {
                property: "mimeType";
                value: "image"
            },
            GalleryContainsFilter {
                property: "mimeType";
                value: "video/mp4"
            },
            GalleryContainsFilter {
                property: "mimeType";
                value: "video/3gpp"
            },
            GalleryContainsFilter {
                property: "mimeType";
                value: "application/vnd.rn-realmedia"
            },
            GalleryContainsFilter {
                property: "mimeType";
                value: "video/quicktime"
            },
            GalleryContainsFilter {
                property: "mimeType";
                value: "video/x-flv"
            },
            GalleryContainsFilter {
                property: "mimeType";
                value: "video/x-msvideo"
            }
        ]
    }
    property bool busy: pModel.progress < 1
}
