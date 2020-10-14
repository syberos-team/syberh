import hybridJs from '../../hybrid';

export default function videoMixin() {
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('video', [
        {
            namespace: 'play',
            os: ['syberos'],
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'fileUrl',
                );
                hybridJs.callInner.apply(this, args);
            },
        },
    ]);
}
