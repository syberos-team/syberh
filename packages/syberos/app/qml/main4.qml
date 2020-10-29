import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "./framework/js/syber.js" as Syberh
import "./framework"

CPageStackWindow {
    initialPage: SWebview4 {
        id:spage
        surl: helper.getHomePage()
        Component.onCompleted: {
            console.log("SWebview4: onCompleted ,url:", spage.surl)
            Syberh.init(spage,spage)
        }
    }
}
