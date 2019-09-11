export default function audioMixin (hybrid) {
  const hybridJs = hybrid;
  const innerUtil = hybridJs.innerUtil;

  hybridJs.extendModule('audio', [{
    namespace: 'startAudioRecorder',
    os: ['syber'],
    defaultParams: {
    },
    runCode (...rest) {
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
      );
      hybridJs.callInner.apply(this, args);
    },
  }, {
    namespace: 'audio',
    namespace: 'stopAudioRecorder',
    os: ['syber'],
    defaultParams: {
    },
    runCode (...rest) {
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
      );
      hybridJs.callInner.apply(this, args);
    },
  }, {
    namespace: 'audio',
    namespace: 'startAudioPlay',
    os: ['syber'],
    defaultParams: {
      path: '',
    },
    runCode (...rest) {
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'path',
      );
      hybridJs.callInner.apply(this, args);
    },
  }, {
    namespace: 'audio',
    namespace: 'stopAudioPlay',
    os: ['syber'],
    defaultParams: {
    },
    runCode (...rest) {
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
      );
      hybridJs.callInner.apply(this, args);
    },
  }]);
}
