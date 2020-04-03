import osMixin from './core/os';
import promiseMixin from './core/promise';
import errorMixin from './core/error';
import proxyMixin from './core/proxy';
import jsbridgeMixin from './core/jsbridge';
import callinnerMixin from './core/callinner';
import defineapiMixin from './core/defineapi';
import callnativeapiMixin from './core/callnativeapi';
import initMixin from './core/init';
import innerUtilMixin from './core/innerutil';
import registerMixin from './core/register';

export default function mixin() {

    osMixin();
    promiseMixin();
    errorMixin();
    // 赖于promise，是否有Promise决定返回promise对象还是普通函数
    proxyMixin();
    // 依赖于showError，globalError，os
    jsbridgeMixin();
    // api没有runcode时的默认实现，依赖于jsbridge与os
    callinnerMixin();
    // 依赖于os，Proxy，globalError，showError，以及callInner
    defineapiMixin();
    // 依赖于JSBridge，Promise,sbridge
    callnativeapiMixin();
    // init依赖与基础库以及部分原生的API
    initMixin();
    // 给API快速使用的内部工具集
    innerUtilMixin();
    // 插件注册到syberh上
    registerMixin();
}
