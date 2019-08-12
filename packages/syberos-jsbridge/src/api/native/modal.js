export default function modalMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('modal', [{
        namespace: 'alert',
        os: ['syber'],
        defaultParams: {
            title: '',
            message: '',
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'title',
                'message');
            
            hybridJs.callInner.apply(this, args);
        },
    }])
}