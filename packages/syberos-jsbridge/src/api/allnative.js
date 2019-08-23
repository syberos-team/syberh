import modalMixin from './native/modal';
import webviewMix from './native/webview';
import runtimeMixin from './native/runtime';
import deviceMixin from './native/device';
import pageMixin from './native/page';
import navigatorMixin from './native/navigator';
import utilMixin from './native/util';
import downloadMixin from './native/download';
import telephonyMixin from './native/telephony';
import storageMixin from './native/storage';
import systemMixin from './native/system';
import networkMixin from './native/network';
import captureMixin from './native/capture';

// const hybridJs = window.syber;
export default function allNative(hybridJs) {
    // 下载模块
    downloadMixin(hybridJs);
    modalMixin(hybridJs);
    webviewMix(hybridJs);
    runtimeMixin(hybridJs);
    deviceMixin(hybridJs);
    pageMixin(hybridJs);
    navigatorMixin(hybridJs);
    utilMixin(hybridJs);
    telephonyMixin(hybridJs);
    storageMixin(hybridJs);
    systemMixin(hybridJs);
    networkMixin(hybridJs);
    captureMixin(hybridJs);
}
