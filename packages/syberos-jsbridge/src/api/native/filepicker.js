export default function filepickerMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('filepicker', [
        {
            namespace: 'open',
            os: ['syber'],
            defaultParams: {},
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(this, rest);
                hybridJs.callInner.apply(this, args);
            },
        },
    ]);
}
