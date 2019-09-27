export default function deviceMixin (hybrid) {
  const hybridJs = hybrid;
  const innerUtil = hybridJs.innerUtil;

  hybridJs.extendModule('device', [{
    namespace: 'setOrientation',
    os: ['syberos'],
    defaultParams: {
      // 1表示竖屏，0表示横屏，-1表示跟随系统
      orientation: 1,
    },
  }, {
    namespace: 'getDeviceId',
    os: ['syberos'],
  }, {
    namespace: 'getVendorInfo',
    os: ['syberos'],
  }, {
    namespace: 'getNetWorkInfo',
    os: ['syberos'],
  }, {
    namespace: 'callPhone',
    os: ['syberos'],
    defaultParams: {
      phoneNum: '',
    },
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'phoneNum');

      hybridJs.callInner.apply(this, args);
    },
  }, {
    namespace: 'sendMsg',
    os: ['syberos'],
    defaultParams: {
      phoneNum: '',
      message: '',
    },
    runCode (...rest) {
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
    os: ['syberos'],
  }, {
    namespace: 'vibrate',
    os: ['syberos'],
    defaultParams: {
      duration: 500,
    },
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'duration');

      hybridJs.callInner.apply(this, args);
    },
  }]);
}