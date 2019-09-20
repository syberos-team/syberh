export default function authMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('webview', [
        {
            namespace: 'reload',
            os: ['syber'],
        },
        {
            namespace: 'goBack',
            os: ['syber'],
        },
        {
            namespace: 'goForward',
            os: ['syber'],
        },
        {
            namespace: 'navigateTo',
            os: ['syber'],
        },
        {
            namespace: 'reLaunch',
            os: ['syber'],
        },
        {
            namespace: 'redirectTo',
            os: ['syber'],
            defaultParams: {
                url: '',
            },
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'url',
                );
                hybridJs.callInner.apply(this, args);
            },
        },
    ]);
}
