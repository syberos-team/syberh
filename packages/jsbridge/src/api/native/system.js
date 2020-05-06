import hybridJs from '../../hybrid';

export default function systemMixin() {
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('system', [{
        namespace: 'aboutPhone',
        os: ['syberos'],
        defaultParams: {
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
            );
            hybridJs.callInner.apply(this, args);
        },
    }]);
}
