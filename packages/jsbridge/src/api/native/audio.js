export default function audioMixin (hybrid) {
  const hybridJs = hybrid;
  const innerUtil = hybridJs.innerUtil;

  hybridJs.extendModule('audio', [{
    namespace: 'start',
    os: ['syberos'],
    defaultParams: {
      path: '',
      position: 0,
    },
    runCode (...rest) {
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'path',
        'position',
      );
      hybridJs.callInner.apply(this, args);
    },
  }, {
    namespace: 'pause',
    os: [''],
  }, {
    namespace: 'resume',
    os: [''],
    defaultParams: {
      position: 0,
    },
    runCode (...rest) {
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'position',
      );
      hybridJs.callInner.apply(this, args);
    },
  }, {
    namespace: 'stop',
    os: [''],
  }]);
}