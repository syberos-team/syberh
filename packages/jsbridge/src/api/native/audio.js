import hybridJs from '../../hybrid';

export default function audioMixin () {
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
    os: ['syberos'],
  }, {
    namespace: 'resume',
    os: ['syberos'],
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
    os: ['syberos'],
  }]);
}