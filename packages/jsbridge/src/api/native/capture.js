export default function captureMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('camera', [{
        namespace: 'takePhoto',
        os: ['syber'],
        defaultParams: {
            enableCut: false,
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'enableCut',
            );
            hybridJs.callInner.apply(this, args);
        },
    }]);
}
