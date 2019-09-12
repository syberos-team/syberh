import QtQuick 2.0
import com.syberos.basewidgets 2.0
import com.syberos.api 1.0

CPageStackWindow {
    Component.onCompleted: console.log("=======Completed Running!")
    initialPage: CPage {

        id: root
        width: parent.width
        height: parent.height
        onStatusChanged: {
            //Component.Ready以后在初始化动态组件
            if (status === Component.Ready) {
                console.log('\n -----------------root', root.width, '\n')

                syberh.render(root)

            }
        }
    }
}
