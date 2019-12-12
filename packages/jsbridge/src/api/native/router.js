export default function authMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('router', [
        {
            namespace: 'reload',
            os: ['syberos'],
        },
        {
            namespace: 'goBack',
            os: ['syberos'],
        },
        {
            namespace: 'goForward',
            os: ['syberos'],
        },
        {
            namespace: 'reLaunch',
            os: ['syberos'],
            defaultParams: {
                url: '',
                data: {},
            },
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'url',
                    'data',
                );
                const options = args[0];

                // 将额外数据拼接到url中
                options.url = innerUtil.getFullUrlByParams(options.url, options.data);
                // 去除无用参数的干扰
                options.data = undefined;

                options.dataFilter = (res) => {
                    const newRes = res;

                    if (!innerUtil.isObject(newRes.result.resultData)) {
                        try {
                            newRes.result.resultData = JSON.parse(newRes.result.resultData);
                        } catch (e) { }
                    }

                    return newRes;
                };

                args[0] = options;
                hybridJs.callInner.apply(this, args);
            },
        },
        {
            namespace: 'navigateTo',
            os: ['syberos'],
            defaultParams: {
                url: '',
                data: {},
            },
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'url',
                    'data',
                );
                const options = args[0];

                // 将额外数据拼接到url中
                options.url = innerUtil.getFullUrlByParams(options.url, options.data);
                // 去除无用参数的干扰
                options.data = undefined;

                options.dataFilter = (res) => {
                    const newRes = res;

                    if (!innerUtil.isObject(newRes.result.resultData)) {
                        try {
                            newRes.result.resultData = JSON.parse(newRes.result.resultData);
                        } catch (e) { }
                    }

                    return newRes;
                };

                args[0] = options;
                hybridJs.callInner.apply(this, args);
            },
        },
        {
            namespace: 'reLaunch',
            os: ['syberos'],
        },
        {
            namespace: 'redirectTo',
            os: ['syberos'],
            defaultParams: {
                url: '',
                data: {},
            },
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'url',
                    'data',
                );
                const options = args[0];

                // 将额外数据拼接到url中
                options.url = innerUtil.getFullUrlByParams(options.url, options.data);
                // 去除无用参数的干扰
                options.data = undefined;

                options.dataFilter = (res) => {
                    const newRes = res;

                    if (!innerUtil.isObject(newRes.result.resultData)) {
                        try {
                            newRes.result.resultData = JSON.parse(newRes.result.resultData);
                        } catch (e) { }
                    }

                    return newRes;
                };

                args[0] = options;
                hybridJs.callInner.apply(this, args);
            },
        },
        {
            namespace: 'navigateBack',
            os: ['syberos'],
            defaultParams: {
                delta: 1,
            },
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'delta',
                );
                hybridJs.callInner.apply(this, args);
            },
        },
        {
            namespace: 'setTitle',
            os: ['syberos'],
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'title',
                );
                hybridJs.callInner.apply(this, args);
            },
        },
        {
            namespace: 'setBackgroundColor',
            os: ['syberos'],
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'backgroundColor',
                );
                hybridJs.callInner.apply(this, args);
            },
        },
        {
            namespace: 'setNavigationBarColor',
            os: ['syberos'],
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'color',
                    'backgroundColor',
                );
                hybridJs.callInner.apply(this, args);
            },
        },
        {
            namespace: 'getCurrentPages',
            os: ['syberos'],
        },
        {
            namespace: 'setPageOrientation',
            os: ['syberos'],
            runCode(...rest) {
                // 兼容字符串形式
                const args = innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'orientation',
                );
                hybridJs.callInner.apply(this, args);
            },
        },
    ]);
}
