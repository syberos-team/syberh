import QtQuick 2.3
import com.syberos.basewidgets 2.0
import com.syberos.photos.extension 1.0

CPage {
    id: mainPage

    property var urls: []
    property string current
    /*!
        \qmlproperty variant CEditGridViewPage::toolButtonNames
        工具栏上按钮的名字，它的值应该是一个数组
    */
    property variant toolButtonNames: ["取消", "取消12323"]

    /*!
        \qmlproperty variant CEditGridViewPage::toolButtonNames
        工具栏上按钮的名字，它的值应该是一个数组
    */
    property bool returnEable: false

    /*! 按钮的高度，默认值为60*/
    property int buttonHeight: 80

    /*! 按钮的颜色*/
    property color buttonColor: "#eeeff1"

    /*! 按钮文本颜色*/
    property color textColor: "#ffffff"

    /*! 按钮文本大小*/
    property int textFontSize: 28

    /*! 成功信号*/
    signal success()


    // 监听返回事件，取消按钮点击才生效
    Keys.onReleased: {
        console.log('listPreview Keys.onReleased',Keys.onReleased)

        if(event.key === Qt.Key_Back || event.key === Qt.Key_Escape) {
            event.accepted = true

            if(returnEable) {
                // 成功信号
                success()
                // 重置
                returnEable = false
                // 点击取消返回页面
                pageStack.pop()
            }
        }

    }



    /*! 背景, 不允许定制 */
    Rectangle{
        id:background
        anchors.fill: parent
        color: "#000000"
        z: 1
    } /*! end of Rectangle */


    /*! 预览组件 */
    CImageListPreview {
        id: listPreview
        z: 2
    }

    /*! 按钮区域 */
    MouseArea {
       id: btnWrap
       z: 8
       width: parent.width
       height: buttonHeight
       anchors.bottom: parent.bottom

       Timer{ id: disabledTimer; interval: 400 } // 防止连续点击按钮
       Rectangle{ anchors.fill: parent; color: "#000000" }

       onCanceled: buttonName.opacity = 1.0
       onPressed: buttonName.opacity = 0.5
       onReleased: {
           // 成功信号
           success()
           // 重置
           returnEable = false
           // 点击取消返回页面
           pageStack.pop()
           disabledTimer.restart()
           buttonName.opacity = 1.0
       }

       Text{
           id: buttonName
           font.pixelSize: textFontSize
           color: textColor
           text: "取消"
           anchors.left: parent.left
           anchors.leftMargin: 40
       }
   }


    function showPage (params) {
        urls = params.urls || []
        current = params.current ? params.current : urls.length > 0 ? urls[0] : ''

        // 清空lstModel
        lstModel.clear()

        listPreview.model = lstModel


        urls.forEach(function (item) {
            lstModel.append({url: item})
        })

        var idx = urls.indexOf(current)
        listPreview.currentIndex  = idx
    }

    SPhotoPreviewModel{ id: lstModel }
}

