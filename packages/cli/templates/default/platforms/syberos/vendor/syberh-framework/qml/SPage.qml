import QtQuick 2.0
import QtQuick.Window 2.2
import com.syberos.basewidgets 2.0
import "../js/util/log.js" as LOG
import "../js/syber.js" as Syberh

SWebview{
    id:spage
    surl:"file://" + helper.getWebRootPath() + "/index.html"
    // surl: "chrome://gpu/"
    // surl: "http://webglreport.com"
    // surl: "http://sdk.iexplorer.geovis.online/examples/index.html#BasicLayer"
    Component.onCompleted: {
        LOG.logger.verbose("SPage:onCompleted ,url:[%s]",spage.surl)
        Syberh.init(spage,spage)
    }
}
