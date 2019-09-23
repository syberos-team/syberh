import modalMixin from './native/modal';
import routerMix from './native/router';
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
import clipboardMixin from './native/clipboard';
import recordMixin from './native/record';
import packageMixin from './native/package';
import filepickerMixin from './native/filepicker';
import networkInfoMixin from './native/networkInfo';
import batteryMixin from './native/battery';
import networkDisabledMixin from './native/networkDisabled';
import networkEnabledMixin from './native/networkEnabled';
import fileManagerMixin from './native/fileManager';
import pathMixin from './native/path';
import imageMixin from './native/image';
import uploadMixin from './native/upload';


// const hybridJs = window.syber;
export default function allNative (hybridJs) {
  // 下载模块
  downloadMixin(hybridJs);
  modalMixin(hybridJs);
  routerMix(hybridJs);
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
  clipboardMixin(hybridJs);
  recordMixin(hybridJs);
  networkInfoMixin(hybridJs);
  batteryMixin(hybridJs);
  networkDisabledMixin(hybridJs);
  networkEnabledMixin(hybridJs);
  filepickerMixin(hybridJs);
  fileManagerMixin(hybridJs);
  packageMixin(hybridJs);
  pathMixin(hybridJs);
  filepickerMixin(hybridJs);
  imageMixin(hybridJs);
  uploadMixin(hybridJs);
}