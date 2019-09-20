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
import org.nemomobile.thumbnailer 1.0
import com.syberos.photos.extension 1.0


CImageListPreview{
    id: list

    /*! 如果mime为视频则显示图标 */
    Loader {
        id: privateData
        property int crementStatus: -1
        width: 120; height: 120
        parent: list.currentItem
        anchors.centerIn: parent
        active: list.currentItem && list.currentItem.isVideoFile
        asynchronous : true
        sourceComponent: Image {
            source: "../images/video.png"
            MouseArea {
                anchors.fill: parent; anchors.margins: -10
                onClicked: {
                    gApp.openUrl("video://play?fileuri=" + encodeURIComponent( decodeURIComponent( list.currentItem.source )));
                }
            }
        }
    }

    onFlickDecreased:{
        if(list.currentIndex > 0){
            list.highlightItem.reset()
            list.decrementCurrentIndex()
            list.positionViewAtIndex(list.currentIndex, ListView.Center)
        }
    }

    onFlickIncreased:{
        if(list.currentIndex < list.count - 1){
            list.highlightItem.reset()
            list.incrementCurrentIndex()
            list.positionViewAtIndex(list.currentIndex, ListView.Center)
        }
    }
}

