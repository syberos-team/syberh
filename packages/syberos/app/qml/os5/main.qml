import QtQuick 2.12
import com.syberos.basewidgets 2.0
import "../js/syber.js" as Syberh


CPageStackWindow {
    initialPage: SWebview {
        id:spage
        surl: helper.getHomePage()
        Component.onCompleted: {
            console.log("SWebview: onCompleted ,url:", spage.surl)
            Syberh.init(spage,spage)
        }
    }
}
