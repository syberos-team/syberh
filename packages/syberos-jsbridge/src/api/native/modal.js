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
    }, {
        namespace: 'confirm',
        os: ['syber'],
        defaultParams: {
            title: '',
            titleIcon: '',
            content: '',
            showCancel: true,
            cancelText: '取消',
            cancelColor: '',
            confirmText: '确定',
            showLoading: false,
            confirmColor: '',
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'title',
                'titleIcon',
                'content',
                'showCancel',
                'cancelText',
                'cancelColor',
                'confirmText',
                'showLoading',
                'confirmColor',
                );
            
            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'prompt',
        os: ['syber'],
        defaultParams: {
            title: '',
            titleIcon: '',
            content: '',
            showCancel: true,
            cancelText: '取消',
            cancelColor: '',
            confirmText: '确定',
            showLoading: false,
            confirmColor: '',
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'title',
                'titleIcon',
                'content',
                'showCancel',
                'cancelText',
                'cancelColor',
                'confirmText',
                'showLoading',
                'confirmColor',
                );
            
            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'toast',
        os: ['syber'],
        defaultParams: {
            title: '',
            icon: '',
            duration: 1500,
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
    }])
}