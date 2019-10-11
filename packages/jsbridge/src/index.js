import mixin from './mixin';
import allNative from './api/allnative';

const hybridJs = {};

mixin(hybridJs);

allNative(hybridJs);
//使用全局变量version
hybridJs.version = JVERSION;

export default hybridJs;