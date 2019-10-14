/*!
* This file is part of hybrid-core
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd.
All rights reserved.
*
* Authors:
* xuejun <xuejun@syberos.com>
*
* This software, including documentation, is protected by
copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are
reserved.
*/
import com.syberos.multimedia.camera 1.0
import com.syberos.basewidgets 2.0
import QtQuick 2.0

CameraPlugin {
    id: __cameraPlugin
    enableCut:false
    signal imageCancele

    Component.onCompleted:{
        gScreenInfo.setStatusBar(false)
    }
    Component.onDestruction :{
        gScreenInfo.setStatusBar(true);
        gScreenInfo.setStatusBarStyle("black");
        imageCancele();
    }

}
