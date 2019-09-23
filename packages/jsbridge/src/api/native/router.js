export default function authMixin (hybrid) {
  const hybridJs = hybrid;
  const innerUtil = hybridJs.innerUtil;

  hybridJs.extendModule('router', [
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
      namespace: 'reLaunch',
      os: ['syber'],
      defaultParams: {
        url: '',
        data: {}
      },
      runCode (...rest) {
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
      os: ['syber'],
      defaultParams: {
        url: '',
        data: {}
      },
      runCode (...rest) {
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
      os: ['syber'],
    },
    {
      namespace: 'redirectTo',
      os: ['syber'],
      defaultParams: {
        url: '',
        data: {}
      },
      runCode (...rest) {
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
      os: ['syber'],
      defaultParams: {
        delta: 1,
      },
      runCode (...rest) {
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
      namespace: 'getCurrentPages',
      os: ['syber']
    }
  ]);
}
