import hybridJs from '../../hybrid';

export default function recordMixin () {
  const innerUtil = hybridJs.innerUtil;

  hybridJs.extendModule('record', [{
    namespace: 'list',
    os: ['syberos'],
  }, {
    namespace: 'start',
    os: ['syberos'],
  }, {
    namespace: 'pause',
    os: ['syberos'],
  }, {
    namespace: 'resume',
    os: ['syberos'],
  }, {
    namespace: 'stop',
    os: ['syberos'],
  }, {
    namespace: 'remove',
    os: ['syberos'],
    runCode (...rest) {
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'path',
      );
      hybridJs.callInner.apply(this, args);
    },
  }]);
}