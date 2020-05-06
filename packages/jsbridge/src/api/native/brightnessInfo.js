import hybridJs from '../../hybrid';

export default function brightnessInfoMixin () {
  const innerUtil = hybridJs.innerUtil;

  hybridJs.extendModule('brightness', [{
    namespace: 'brightnessInfo',
    os: ['syberos'],
    defaultParams: {
    },
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
      );
      hybridJs.callInner.apply(this, args);
    },
  },
  {
    namespace: 'setAdaptiveDimmingEnabled',
    os: ['syberos'],
    defaultParams: {
    },
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
      );
      hybridJs.callInner.apply(this, args);
    },
  },
  {
    namespace: 'setAmbientLightSensorEnabled',
    os: ['syberos'],
    defaultParams: {
    },
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
      );
      hybridJs.callInner.apply(this, args);
    },
  },
  {
    namespace: 'setBlankTimeout',
    os: ['syberos'],
    defaultParams: {
    },
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
      );
      hybridJs.callInner.apply(this, args);
    },
  },
  {
    namespace: 'setBrightness',
    os: ['syberos'],
    defaultParams: {
    },
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
      );
      hybridJs.callInner.apply(this, args);
    },
  },
  {
    namespace: 'setDimTimeout',
    os: ['syberos'],
    defaultParams: {
    },
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
      );
      hybridJs.callInner.apply(this, args);
    },
  }
  ]);
}
