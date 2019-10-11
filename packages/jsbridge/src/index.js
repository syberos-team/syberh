import mixin from './mixin';
import allNative from './api/allnative';
const pkgJSON = require('../package.json')


const hybridJs = {};

mixin(hybridJs);

allNative(hybridJs);

hybridJs.version = `${pkgJSON.version}`;

export default hybridJs;