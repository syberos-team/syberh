import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "./framework/js/syber.js" as Syberh
import "./framework"

CPageStackWindow {
    initialPage: SWebview59 {
        id:spage
        surl: helper.getHomePage()
        Component.onCompleted: {
            console.log("SPage:onCompleted ,url:[%s]",spage.surl)
            Syberh.init(spage,spage)
        }
    }
}
