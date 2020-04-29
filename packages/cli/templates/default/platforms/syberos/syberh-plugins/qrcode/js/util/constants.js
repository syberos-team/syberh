/*
* This file is part of syberos-settings
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*       Lele Huan <huanlele@syberos.com>
*       Zhenbin Cai <caizhenbin@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

var rate = 1.5;//applets.getSizeRatio();
//rate = function(){
//    var value;
//    switch(gScreenInfo.density){
//    case CScreenInfo.Small :
//        value = 0.75;
//        break;
//    case CScreenInfo.Normal :
//        value = 1;
//        break;
//    case CScreenInfo.Large:
//        value = 1.5;
//        break;
//    case CScreenInfo.ExtraLarge:
//        value = 2;
//        break;
//    }
//    console.log("constantsjs  rate ", value);
//    return value;
//}

var DEFAULT_FONT_FAMILY = "方正兰亭准黑_GBK"//"方正兰亭准黑_GBK"; //"Liberation Sans" // "Droid Sans"

var GROUP_SEPARATOR_HIGHT = 20 * rate


var TITLE_BAR_HEIGHT = 76 * rate

var INPUT_ITEM_ICON_WIDTH = 20 * rate
var INPUT_ITEM_ICON_HEIGHT = 20 * rate
var INPUT_ITEM_LEFTMARGIN = 50 * rate
var INPUT_ITEM_ICON_BOTTOMMARGIN = 6 * rate
var INPUT_ITEM_TEXT_BOTTOMMARGIN = 10 * rate
//列表背景颜色
var LIST_ITEM_BGCOLOR = "#d9d9d9"
var LIST_ITEM_HEIGHT = 60 * rate
var LIST_ITEM_ROW_SPACEING = 15 * rate
var LIST_ITEM_LEFT_MARGIN = 20 * rate
var LIST_TITLE_SIZE = 15 * rate

var LIST_TITLE_COLOR = "#5e5e5e"
var LIST_PRESSED_COLOR = "#ffffff"
var LIST_TITLE_DISABLE_COLOR = "#c2cccc"
var LIST_TITLE_COLOR_PRESSED = "#797979"
var LIST_TITLE_COLOR_INVERTED = "#ffffff"
var LIST_TITLE_COLOR_PRESSED_INVERTED = "#797979"

var LIST_SUBTILE_SIZE = 15 * rate
var LIST_SUBTITLE_COLOR = "#999999"
var LIST_SUBTITLE_COLOR_PRESSED = "#797979"
var LIST_SUBTITLE_COLOR_INVERTED = "#C8C8C8"
var LIST_SUBTITLE_COLOR_PRESSED_INVERTED = "#797979"

var LIST_SUBHEAD_BGCOLOR = "#EDF0F0"
var LIST_SUBHEAD_HEIGHT = 74 * rate
var LIST_SUBHEAD_FONT_COLOR = "#787777"
var LIST_SUBHAED_FONT_SIZE = 24 * rate
var LIST_SUBHEAD_BOTTOM_HEIGHT = 18 * rate
var LIST_SEPARETOR_LINE_HEIGHT = 1 * rate
var LIST_SEPARETOR_LINE_COLOR = "#e8e8e8"
var LIST_TOP_INTERVAL_HEIGHT = 24 * rate
var LIST_BTOTTOM_INTERVAL_HEIGHT = 24 * rate

var LIST_ICON_MARGIN_LEFT = 20 * rate
var LIST_ICON_MARGIN_RIGHT = 20 * rate
var LIST_ICON_WIDTH = 30 * rate
var LIST_ICON_HEIGHT = 30 * rate
var LIST_RIGHTICON_WIDTH = 10 * rate
var LIST_RIGHTICON_HEIGHT = 20 * rate
var LIST_MAIN_SUB_SEPARATOR = 10 * rate


var LENGTH_SCREEN = rate * 720;
var HEIGHT_SCREEN = rate * 1280;

var SCAN_ITEM_H = rate* 100;
function fontSize(size){
    return Number(size) * rate;
}
var FONT_SIZE_08 = 8 * rate;
var FONT_SIZE_10 = 10 * rate;
var FONT_SIZE_11 = 11 * rate;
var FONT_SIZE_12 = 12 * rate;
var FONT_SIZE_13 = 13 * rate;
var FONT_SIZE_14 = 14 * rate;
var FONT_SIZE_16 = 16 * rate;
var FONT_SIZE_18 = 18 * rate;
var FONT_SIZE_22 = 22 * rate;

// show check version
var SHOW_CHECK_VERSION_PAGE = "1";
// show version update
var SHOW_VERSION_UPDATE_PAGE = "2";
// clear version page
var CLEAR_VERSION_PAGE = "0";
// show install error
var SHOW_INSTALL_ERROR_PAGE = "4";
// download SUCCESS
var  DOWNLOAD_STATUS_SUCCESS = "0";
var  INSTALL_STATUS_SUCCESS = "3";
// Home name IDS
var THEME_NAMEID_INSPECTION = "Inspection";
var THEME_NAMEID_OPERATION = "Operation";
var THEME_NAMEID_INVENTORY = "Inventory";
var THEME_NAMEID_MAINTENANCE = "Maintenance";
var THEME_NAMEID_DEVICE_QUERY = "DeviceQuery";
var THEME_NAMEID_STANDARDIZATION = "Standardization";
var THEME_NAMEID_RECTIFICATION = "Rectification";
var THEME_NAMEID_RECTIFICATION_TASK = "RectificationTasks";
var THEME_NAMEID_RECTIFICATION_CONFIRM = "RectificationConfirm";
var THEME_NAMEID_COMPREHENSIVE_BUSINESS = "ComprehensiveBusiness";
var THEME_NAMEID_DATAREPORT = "DataReport";
var THEME_NAMEID_DAILYTASK = "DailyTask";
var THEME_NAMEID_USER_CARD = "UserCard";
var THEME_NAMEID_SETTINGS = "Settings";
var THEME_NAMEID_MESSAGES = "Messages";
var THEME_NAMEID_SCANTASK = "ScanTask";
var THEME_NAMEID_KNOWLEDGE = "KnowLedge";
var THEME_NAMEID_DEVICE_TASKING = "DeviceTaking";
var THEME_NAMEID_DEVICE_ALLOT = "DeviceAllot";
var THEME_NAMEID_RFID_ASSOCATION = "RFIDAssociation";
var THEME_NAMEID_LOGIN_LOGO = "LoginLogo";
var THEME_NAMEID_LOGIN_TITLE = "LoginTitle";
var THEME_NAMEID_LOGIN_SUB_TITLE = "LoginSubTitle";
var THEME_NAMEID_LOGIN_USER_LEFT_ICON = "LoginUserLeftIcon";
var THEME_NAMEID_LOGIN_USER_RIGHT_ICON = "LoginUserRightIcon";
var THEME_NAMEID_LOGIN_PASSWORD_LEFT_iCON = "LoginPasswrdLeftIcon";
var THEME_NAMEID_LOGIN_BTN = "LoginBtn";
var THEME_NAMEID_LOGOUT_BTN = "LogoutBtn";
var THEME_NAMEID_HOME_LOGO = "HomeLogo";
var MAX_DOWNLOAD_COUNT = 3;

