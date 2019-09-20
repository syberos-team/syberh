export default function audioMixin (hybrid) {
  const hybridJs = hybrid;
  const innerUtil = hybridJs.innerUtil;

  hybridJs.extendModule('audio', [{
    namespace: 'recorderList',
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
    namespace: 'startRecorder',
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
    namespace: 'pauseRecorder',
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
    namespace: 'continueRecorder',
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
    namespace: 'stopRecorder',
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
    namespace: 'delRecorder',
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
    namespace: 'startPlay',
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
    namespace: 'pausePlay',
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
    namespace: 'continuePlay',
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
    namespace: 'stopPlay',
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