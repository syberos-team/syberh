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
<<<<<<< HEAD

    }
       
=======
        Component.onCompleted: {
            /// 通过获取Object的方式访问对象导出的接口
          var status =  NativeSdkManager.getUiSource("CameraHandler*","").getCameraFlashMode();
        }
<<<<<<< HEAD
=======
>>>>>>> Revert "docs: 修复文档内示例代码资源引用不正确 (#4014)"
>>>>>>> hanagm-master

       
        CButton {
           x: root.width-100
            y: 60
        }
}
