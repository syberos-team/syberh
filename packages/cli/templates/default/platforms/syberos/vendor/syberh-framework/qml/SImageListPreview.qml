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

