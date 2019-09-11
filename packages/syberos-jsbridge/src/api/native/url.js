export default function urlMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('url', [{
        namespace: 'openUrl',
        os: ['syber'],
        defaultParams: {
            scheme: '',
            path: '',
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
    }]);
}