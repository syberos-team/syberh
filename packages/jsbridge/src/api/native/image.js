export default function imageMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('image', [
        {
            namespace: 'choose',
            os: ['syber'],
            defaultParams: {
                count: 9,
            },
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'count',
                );
                hybridJs.callInner.apply(this, args);
            },
        }, {
            namespace: 'select',
            os: ['syber'],
            defaultParams: {},
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                );
                hybridJs.callInner.apply(this, args);
            },
        },
    ]);
}
