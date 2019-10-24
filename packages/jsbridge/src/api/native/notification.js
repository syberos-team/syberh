export default function notificationMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('notification', [{
        namespace: 'badgeShow',
        os: ['syberos'],
        defaultParams: {
            appid: '',
            num: 0,
        },
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'appid',
                'num',
            );
            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'sendNotification',
        os: ['syberos'],
        defaultParams: {
            type: 3,
            title: '',
            subtitle: '',
        },
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'type',
                'title',
                'subtitle',
            );
            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'removeNotification',
        os: ['syberos'],
    }]);
}