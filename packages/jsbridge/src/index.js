import mixin from './mixin';
import allNative from './api/allnative';

const hybridJs = {};

mixin(hybridJs);

allNative(hybridJs);

hybridJs.Version = '1.1.1';

export default hybridJs;