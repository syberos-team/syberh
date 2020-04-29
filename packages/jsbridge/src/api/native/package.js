export default function packageMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('package', [{
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