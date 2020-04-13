import QtQuick 2.0
import syberh_filepicker 1.0
import com.syberos.basewidgets 2.0

SFilesPicker {
  id: filepicker
  onStatusChanged:{
    if(status == CPageStatus.WillShow){
        console.log("SFilesPicker WillShow")
        filepicker.statusBarHoldEnabled = true
        gScreenInfo.setStatusBarStyle("black");
        gScreenInfo.setStatusBar(true);
    }
  }
}
