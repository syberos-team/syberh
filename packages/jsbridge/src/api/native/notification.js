import hybridJs from '../../hybrid';

export default function notificationMixin() {
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('notification', [{
        namespace: 'badgeShow',
        os: ['syberos'],
        defaultParams: {
            appId: '',
            num: 0,
        },
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'appId',
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
        namespace: 'removeAllNotifications',
        os: ['syberos'],
    }, {
        namespace: 'removeNotification',
        os: ['syberos'],
        defaultParams: {
            updateId: '',
        },
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'updateId',
            );
            hybridJs.callInner.apply(this, args);
        },
    }]);
}