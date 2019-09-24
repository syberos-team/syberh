export default function recordMixin (hybrid) {
  const hybridJs = hybrid;
  const innerUtil = hybridJs.innerUtil;

  hybridJs.extendModule('record', [{
    namespace: 'list',
    os: ['syber']
  }, {
    namespace: 'startRecorder',
    os: ['syber']
  }, {
    namespace: 'pauseRecorder',
    os: ['syber']
  }, {
    namespace: 'continueRecorder',
    os: ['syber']
  }, {
    namespace: 'stopRecorder',
    os: ['syber']
  }, {
    namespace: 'delRecorder',
    os: ['syber'],
    runCode (...rest) {
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'path'
      );
      hybridJs.callInner.apply(this, args);
    }
  }, {
    namespace: 'startPlay',
    os: ['syber'],
    runCode (...rest) {
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'path'
      );
      hybridJs.callInner.apply(this, args);
    }
  }, {
    namespace: 'pausePlay',
    os: ['syber']
  }, {
    namespace: 'continuePlay',
    os: ['syber']
  }, {
    namespace: 'stopPlay',
    os: ['syber']
  }]);
}