/*!
* \file CommonButton.qml
* \brief 公共控件，通用页面
*
*公共控件，通用页面
*
*\author 桓乐乐 huanlele@syberos.com
*\version 1.0
*\date 2015/9/7
*/
import QtQuick 2.0
import com.syberos.basewidgets 2.0
/*!
  \class CommonPage
  \inModule 公共控件
  \brief 公共控件，通用页面
  \ingroup common
  公共控件，通用页面，Page为显示/隐藏时enabled属性为true/false
*/
CPage{
    statusBarHoldEnabled: true
    statusBarHoldItemColor: "red"
    orientationPolicy: CPageOrientation.LockPortrait
    enabled: CPageStatus.Show
}
