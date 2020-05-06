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

Timer{
    id: selectAllTimer

    property int selectedCount: 0
    property var selectedIndex: mainPage.arr
    property int viewCount: 0
    property bool animating: false

    property bool pressAndHoldFlag: false

    function indexOf(index){
        return selectedIndex.indexOf(index*1); // 使用数字作为判断依据
    }

    function clear(){
        selectedIndex = []
        selectedCount = 0
    }

    function selectIndex(index, mode) {
        if(mode){
            if(indexOf(index) === -1){
                selectedIndex.push(index*1); // 确保push的是数字，以免返回selectedIndex时，返回的是字符串数组
                ++selectedCount;
            }
        }else{
            var tmpIndex = indexOf(index);
            if(tmpIndex > -1){
                selectedIndex.splice(tmpIndex, 1);
                --selectedCount;
            }
        }
    }

    interval: 1
    repeat: true

    property var itemsWithPos: []
    property int times: 0
    property bool selectAllMode: true
    property bool selectAnimationEnabled: true

    function selectStart(shownIndexes, mode){
        var i=0;
        if(selectAnimationEnabled){
            animating = true
            selectAllMode = mode
            times = 0;
            itemsWithPos = shownIndexes;
            start()
        }else{
            if(mode){
                for(i=0; i<viewCount; ++i){
                    if(indexOf(i) === -1){
                        selectedIndex.push(i)
                    }
                }
                selectedCount = viewCount
            }else{
                selectedIndex = []
                selectedCount = 0
            }
            indexStatusChanged(-1)
        }
    }

    onTriggered: {
        var i
        if(times < itemsWithPos.length){
            i = itemsWithPos[times]
            if(selectAllMode){
                if(indexOf(i) === -1){
                    selectedIndex.push(i)
                    selectedCount++
                    indexStatusChanged(i)
                }
            }else{
                var tmpIndex = indexOf(i)
                if(tmpIndex > -1){
                    selectedIndex.splice(tmpIndex, 1)
                    --selectedCount
                    indexStatusChanged(i)
                }
            }
            ++times
        }else{
            stop()
            itemsWithPos = []
            if(selectAllMode){
                for(i=0; i<viewCount; ++i){
                    if(indexOf(i) === -1){
                        selectedIndex.push(i)
                    }
                }
                selectedCount = viewCount
            }else{
                selectedIndex = []
                selectedCount = 0
            }
            indexStatusChanged(-1)
            animating = false
        }
    }

}
