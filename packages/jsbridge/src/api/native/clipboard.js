export default function clipboardMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('clipboard', [{
        namespace: 'setClipboardData',
        os: ['syberos'],
        defaultParams: {
            data: '',
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'data',
            );
            hybridJs.callInner.apply(this, args);
        },
    },{
        namespace: 'getClipboardData',
        os: ['syberos'],
        defaultParams: {
            data: '',
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'data',
            );

            hybridJs.callInner.apply(this, args);
        },
    }
]);
}
