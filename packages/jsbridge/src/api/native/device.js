export default function deviceMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;
    
    hybridJs.extendModule('device', [{
        namespace: 'setOrientation',
        os: ['syber'],
        defaultParams: {
            // 1表示竖屏，0表示横屏，-1表示跟随系统
            orientation: 1,
        },
    }, {
        namespace: 'getDeviceId',
        os: ['syber'],
    }, {
        namespace: 'getVendorInfo',
        os: ['syber'],
    }, {
        namespace: 'getNetWorkInfo',
        os: ['syber'],
    }, {
        namespace: 'callPhone',
        os: ['syber'],
        defaultParams: {
            phoneNum: '',
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'phoneNum');
            
            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'sendMsg',
        os: ['syber'],
        defaultParams: {
            phoneNum: '',
            message: '',
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'phoneNum',
                'message');
            
            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'closeInputKeyboard',
        os: ['syber'],
    }, {
        namespace: 'vibrate',
        os: ['syber'],
        defaultParams: {
            duration: 500,
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'duration');
            
            hybridJs.callInner.apply(this, args);
        },
    }]);
}