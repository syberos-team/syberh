/* eslint-disable no-unused-vars */

// 全局syberos对象,在初始化完成有建立
var SYBEROS = null
// 全局WEBVIEW
var WEBVIEWCORE = currentWebview
// 返回键的值
var KEYCODE_BACK = 16777313
// 当前所有webview对象
var swebviews = []
// 全局
var swebviewCache = {}
// 当前webview
var currentWebview = {}
// 当前webview栈的层数
var webviewdepth = 0
// 最大栈数
var webviewMaxDepth = 5
// 在原生调用完对应的方法后,会执行对应的回调函数id，并删除
var responseCallbacks = {}
// 长期存在的回调，调用后不会删除
var responseCallbacksLongTerm = {}

//是否注册NativeSdkManager
var registrNativeSdkManager = false;
