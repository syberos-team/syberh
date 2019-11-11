/*!
* This file is part of hybrid-core
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*
*   xuejun <xuejun@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

import QtQuick 2.3
import QtQuick.Window 2.2
import com.syberos.basewidgets 2.0

CInputDialog{
    id: inputDialog
    /*! 标题 */
    titleText: ""

    /*! 输入框默认文本 */
    placeholderText: ""

    /*! 点击遮罩层是否可以关闭 */
    canceledOnOutareaClicked: false

    /*! 确认按钮文字 */
    acceptedButtonText: ''

    /*! 取消按钮文字 */
    rejectButtonText: ''
    signal inputBack()

    Component.onDestruction: {
        console.log('Component onDestruction---')
        inputBack();
    }


}





