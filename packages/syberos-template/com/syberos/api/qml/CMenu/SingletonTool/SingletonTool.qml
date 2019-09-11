pragma Singleton
import QtQuick 2.2

QtObject {
    property real currentCursorHeight: 20
    property real textLeftAndRightDefaultMargin: 4
    property int pressDelay: 300
    property int handleHorizontalAdjust: 18
    property int handleVerticalAdjust: 24
    property int handleMargin: 2
    property int handleHeight: 60

    property int menuFixedHeight: 88
    property int statusBarHeight: 48

    property int triangleWidth: 45
    property int triangleHeight: 28
    property int triangleMargin: 15

    property int menuItemWidth: 100
    property int menuItemHeight: 60

    property int pressAndHoldDefaultTimeout: 300

    property int cursorDelegateItemWidth: 4

    property bool startHandleTowardUp: false
    property bool menuArrowTowardUp: true

    property int maximumLength: 10000

    function bound(min,value,max){
        return Math.max(min,Math.min(value,max))
    }
}
