import QtQuick 2.0
import com.syberos.basewidgets 2.0
import QtMultimedia 5.0
import com.syberos.download 1.0
import com.syberos.core 1.0

CPageStackWindow {
    Component.onCompleted: console.log("=======Completed Running!")
    initialPage: CPage {

        id: root
        width: parent.width
        height: parent.height
        onStatusChanged:{
            //Component.Ready以后在初始化动态组件
            if(status===Component.Ready){
                console.log('-----------------root',root.width,'\n')
                 Logic.render(root)
            }
        }

    }
}
