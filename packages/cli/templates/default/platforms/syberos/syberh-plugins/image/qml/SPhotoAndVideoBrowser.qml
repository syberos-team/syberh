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
/*!
    \qmltype
    \inqmlmodule com.syberos.photos
    \since 2.0
    \ingroup controls
    \brief 图片和视频浏览查看视图
 */


SCheckGridView{
    id: scheckgridview

    cellWidth: width/4.0
    cellHeight: cellWidth
    maximumFlickVelocity: 4000
    cacheBuffer: count*cellWidth*cellHeight

    delegate: CCheckGridViewDelegate {
        width: cellWidth
        height: cellHeight
        editLabelRightMargin: env.dp(20)
        editLabelBottomOffset: env.dp(20)
        smooth: false

        Image {
            id: image
            x: 2; y: 2; width: cellWidth - 4; height: cellHeight - 4
            source: "image://nemoThumbnail/" + url
            sourceSize: Qt.size(env.dp(100),env.dp(100))
            asynchronous: true
            fillMode: Image.PreserveAspectCrop
            smooth: false
        }

        /*! 如果mime为视频则显示图标 */
        Loader{
            width: env.dp(120)
            height: env.dp(120)
            anchors.centerIn: parent
            active: (image.status === Image.Ready)
                    && (typeof mimeType != "undefined")
                    && (mimeType.toLowerCase().indexOf("video") != -1)
            sourceComponent: Image {
                source: "../images/video.png"
                sourceSize: Qt.size(env.dp(120), env.dp(120))
            }
        }
    }

    add: Transition {
        PropertyAnimation {
            property: "scale"
            from: 0
            to:1
            duration: 500
            easing.type: Easing.OutCubic
        }
    }
}
