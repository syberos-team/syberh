export default function authMixin(hybrid) {
    const hybridJs = hybrid;

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
            namespace: 'redirectTo',
            os: ['syber'],
            defaultParams: {
                url: '',
            },
        },
    ]);
}
