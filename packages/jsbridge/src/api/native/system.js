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
    },
    {
        //设置系统时间
        namespace: 'setDate',
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
    },
    {
        //截屏
        namespace: 'captureScreen',
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
    },
    {
        //设置系统虚拟按键显示状态
        namespace: 'setVirtualPanel',
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
