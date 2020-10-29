import QtQuick 2.0
import com.syberos.basewidgets 2.0
import "./framework/js/syber.js" as Syberh
import "./framework"

CPageStackWindow {
    initialPage: SWebview{
        id:spage
        surl: helper.getHomePage()
        Component.onCompleted: {
            console.log("SWebview: onCompleted ,url:", spage.surl)
            Syberh.init(spage,spage)
        }
    }
}
