import hybridJs from '../../hybrid';

export default function appMixin() {
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('application', [
        {
            namespace: 'setAppOrientation',
            os: ['syberos'],
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'orientation',
                );
                hybridJs.callInner.apply(this, args);
            },
        },
        {
            namespace: 'quit',
            os: ['syberos'],
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                );
                hybridJs.callInner.apply(this, args);
            }
        }
    ]);
}
