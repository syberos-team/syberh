/*!
* This file is part of hybrid-core
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*
*   xuejun <xuejun@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

import QtQuick 2.3

/*!
    \qmltype CCollisionIndicator
    \inqmlmodule com.syberos.basewidgets
    \since 2.0
    \ingroup controls
    \inherits Item
    \brief 小球碰撞风格的等待动画控件

    小球碰撞风格的等待动画。

    使用示例：

    \qml
    CCollisionIndicator {
        running: true
    }
    \endqml

    \note 自定义大小时长宽比应为3。
*/

Item {
    id: indicator

    /*! 动画是否运行，默认值为 visible。 */
    property bool running: true


    /*! 颜色。 */
    property color color: "#999"

    /*!
        \internal
        下拉时中号小球y方向偏移比例：0～1.0
    */
    property real yOffsetRatio: 0

    /*! 等待动画结束时发出。 */
    signal finished()

    implicitWidth: 150
    implicitHeight: 150

//    /*! 宽度 */
//    property real width: 150

//    /*! 高度 */
//    property real height: 150

    onWidthChanged: height = width;

    onHeightChanged: width = height;

    layer.enabled: true
    layer.effect:
        ShaderEffect {
        id: effect

        property real sizeL: 0
        property real dl: 0
        property real dly: 0
        property real dr: 0
        property real dl1: 0
        property real dr1: 0
        property color bgColor: "transparent"
        property color fgColor: indicator.color

        function start() {
            startAnim.start();
        }

        function stop() {
            loadingAnim.stop();
        }

        Connections {
            target: indicator
            ignoreUnknownSignals: true
            onRunningChanged: {
                if(!indicator.running)
                    effect.stop();
                else if(effect.dly != 0)
                    foldAnim.start();
                else
                    effect.start();
            }
            onYOffsetRatioChanged: {
                if(!indicator.running) {
                    if(effect.sizeL != 0.08)
                        effect.sizeL = 0.08;
                    if(indicator.yOffsetRatio <= 1 && indicator.yOffsetRatio >= -1)
                        effect.dly = -0.2 * indicator.yOffsetRatio;
                }
            }
        }

        Component.onCompleted: {
            if(indicator.running)
                effect.start();
        }

        property real durationRatio: gSystemUtils.durationRatio == 0 ? 1 : gSystemUtils.durationRatio

        /*! 标识动画是否正在进行，只读属性。*/
        readonly property bool animating: foldAnim.running || startAnim.running || loadingAnim.running || stopAnim.running

        NumberAnimation {
            id: foldAnim
            target: effect; property: "dly"; to: 0; duration: durationRatio*800; easing.type: Easing.OutBack
            onStopped: effect.start();
        }

        ParallelAnimation {
            id: startAnim
            NumberAnimation {  //big ball
                target: effect; property: "sizeL"; from: 0; to: 0.08; duration: durationRatio*800; easing.type: Easing.OutElastic;
            }
            SequentialAnimation { //left
                PauseAnimation { duration: durationRatio*300 }
                NumberAnimation { target: effect; property: "dl"; duration: durationRatio*800; from: 0; to: 0.15; easing.type: Easing.OutBack }
            }
            SequentialAnimation { //right
                PauseAnimation { duration: durationRatio*400 }
                NumberAnimation { target: effect; property: "dr"; duration: durationRatio*800; from: 0; to: 0.15; easing.type: Easing.OutBack }
            }
            onStopped: { loadingAnim.start(); }
        }

        ParallelAnimation {
            id: loadingAnim
            SequentialAnimation { //big size ball
                loops: Animation.Infinite
                NumberAnimation { target: effect; property: "sizeL"; duration: durationRatio*1100; from: 0.08; to: 0.07; easing.type: Easing.InOutQuad }
                NumberAnimation { target: effect; property: "sizeL"; duration: durationRatio*1100; from: 0.07; to: 0.08; easing.type: Easing.InOutQuad }
            }
            SequentialAnimation { //left middle size ball
                loops: Animation.Infinite
                NumberAnimation { target: effect; property: "dl"; duration: durationRatio*800; from: 0.15; to: 0.20; easing.type: Easing.InOutQuad }
                NumberAnimation { target: effect; property: "dl"; duration: durationRatio*800; from: 0.20; to: 0.15; easing.type: Easing.InOutQuad }
                PauseAnimation { duration: durationRatio*300 }
            }
            SequentialAnimation { //right middle size ball
                loops: Animation.Infinite
                PauseAnimation { duration: durationRatio*300 }
                NumberAnimation { target: effect; property: "dr"; duration: durationRatio*800; from: 0.15; to: 0.20; easing.type: Easing.InOutQuad }
                NumberAnimation { target: effect; property: "dr"; duration: durationRatio*800; from: 0.20; to: 0.15; easing.type: Easing.InOutQuad }
            }
            SequentialAnimation { //left small size ball
                loops: Animation.Infinite
                NumberAnimation { target: effect; property: "dl1"; duration: durationRatio*800; from: 0.15; to: 0.35; easing.type: Easing.InOutQuad }
                NumberAnimation { target: effect; property: "dl1"; duration: durationRatio*800; from: 0.35; to: 0.15; easing.type: Easing.InOutQuad }
                PauseAnimation { duration: durationRatio*300 }
            }
            SequentialAnimation { //right small size ball
                loops: Animation.Infinite
                PauseAnimation { duration: durationRatio*300 }
                NumberAnimation { target: effect; property: "dr1"; duration: durationRatio*800; from: 0.15; to: 0.35; easing.type: Easing.InOutQuad }
                NumberAnimation { target: effect; property: "dr1"; duration: durationRatio*800; from: 0.35; to: 0.15; easing.type: Easing.InOutQuad }
            }
            onStopped: { stopAnim.start(); }
        }

        ParallelAnimation {
            id: stopAnim
            NumberAnimation { target: effect; property: "dl"; duration: durationRatio*300; to: 0; easing.type: Easing.InBack }
            NumberAnimation { target: effect; property: "dr"; duration: durationRatio*300; to: 0; easing.type: Easing.InBack }
            NumberAnimation { target: effect; property: "dl1"; to: 0; }
            NumberAnimation { target: effect; property: "dr1"; to: 0; }
            SequentialAnimation { //big size ball
                PauseAnimation { duration: durationRatio*300 }
                NumberAnimation { target: effect; property: "sizeL"; duration: durationRatio*300; from: 0.08; to: 0; easing.type: Easing.InOutQuad }
            }
            onStopped: indicator.finished();
        }

        fragmentShader: "
            varying highp vec2 qt_TexCoord0;
            uniform lowp float dl;
            uniform lowp float dr;
            uniform lowp float dl1;
            uniform lowp float dr1;
            uniform lowp float dly;
            uniform lowp vec4 bgColor;
            uniform lowp vec4 fgColor;
            uniform highp float height;
            uniform highp float width;
            uniform highp float sizeL;

            void main() {
                highp float sizeM = 0.06;
                highp float sizeS = 0.02;

                highp vec2 origin = vec2(0.5, 0.5);

                highp vec2 dist;
                highp float val = 0.0;
                highp float t = 0.0;

                dist = origin - qt_TexCoord0.xy;
                val += (sizeL*sizeL) / (dist.x * dist.x + dist.y * dist.y);
                if(dl > 0. || dly != 0.) {
                    dist = origin - vec2(dl, dly) - qt_TexCoord0.xy;
                    val += (sizeM*sizeM) / (dist.x * dist.x + dist.y * dist.y);
                }
                if(dr > 0.) {
                    dist = origin + vec2(dr, 0) - qt_TexCoord0.xy;
                    val += (sizeM*sizeM) / (dist.x * dist.x + dist.y * dist.y);
                }
                if(dl1 > 0.) {
                    dist = origin - vec2(dl1, 0) - qt_TexCoord0.xy;
                    val += (sizeS*sizeS) / (dist.x * dist.x + dist.y * dist.y);
                }
                if(dr1 > 0.) {
                    dist = origin + vec2(dr1, 0) - qt_TexCoord0.xy;
                    val += (sizeS*sizeS) / (dist.x * dist.x + dist.y * dist.y);
                }
                if(val >= 1.1)
                    gl_FragColor = fgColor;
                else if(val > 1.0 && val < 1.1) {
                    t = (1.1 - val)*10.;
                    gl_FragColor = fgColor*(1.0-t) + bgColor*t;
                } else
                    gl_FragColor = bgColor;
            }
            "
    }
}

