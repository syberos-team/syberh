export default function networkMixin(hybrid) {
    const hybridJs = hybrid;

    hybridJs.extendModule('network', [
        {
            namespace: 'request',
            os: ['syberos'],
            defaultParams: {
                /** 请求地址 */
                url: '',
                /** 默认值: "GET")。请求方式 ("POST" 或 "GET")， 默认为 "GET"。*/
                type: '',
                data: ''
            },
        }
        
    ]);
}
