/**
 * 文件下载接口
 * @param hybrid
 */
export default function modalMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;


    hybridJs.extendModule('modal', [{
        namespace: 'toast',
        os: ['syber'],
        defaultParams: {
            title: '',
            icon: '',
            duration: 1500
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'title',
                'icon',
                'duration',
            );

            hybridJs.callInner.apply(this, args);
        },
    }]);
}