import hybridJs from '../../hybrid';

<<<<<<< HEAD:packages/jsbridge/src/api/native/package.js
export default function packageMixin() {
=======
export default function packagesMixin() {
>>>>>>> syber/master:packages/jsbridge/src/api/native/packages.js
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('packages', [{
        namespace: 'openUrl',
        os: ['syberos'],
        defaultParams: {
            scheme: '',
            path: 'index.html',
            params: {},
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject(
                rest,
                'scheme',
                'path',
                'params',
            );

            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'openDocument',
        os: ['syberos'],
        defaultParams: {
            sopid: '',
            uiappid: '',
            action: 'openPage',
            path: 'index.html',
            params: {},
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject(
                rest,
                'sopid',
                'uiappid',
                'action',
                'path',
                'params',
            );

            hybridJs.callInner.apply(this, args);
        },
    }]);
}