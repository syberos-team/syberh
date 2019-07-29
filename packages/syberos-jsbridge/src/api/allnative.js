import uiMixin from './native/ui';
import authMixin from './native/auth';
import runtimeMixin from './native/runtime';
import deviceMixin from './native/device';
import pageMixin from './native/page';
import navigatorMixin from './native/navigator';
import utilMixin from './native/util';
import downloadMixin from './native/download';

//const hybridJs = window.syber;
export default function allNative(hybridJs){
  // 下载模块
  downloadMixin(hybridJs);
  uiMixin(hybridJs);
  authMixin(hybridJs);
  runtimeMixin(hybridJs);
  deviceMixin(hybridJs);
  pageMixin(hybridJs);
  navigatorMixin(hybridJs);
  utilMixin(hybridJs);
}


