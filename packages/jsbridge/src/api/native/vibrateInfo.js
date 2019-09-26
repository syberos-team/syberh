export default function vibratorMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('vibrator', [{
        namespace: 'vibrate',
        os: ['syber'],
        defaultParams: {
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
            );
            hybridJs.callInner.apply(this, args);
        },
    },
    {
        namespace: 'vibrateInfo',
        os: ['syber'],
        defaultParams: {
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
            );
            hybridJs.callInner.apply(this, args);
        },
    },
    {
      namespace: 'setVibratingEnabled',
      os: ['syber'],
      defaultParams: {
      },
      runCode(...rest) {
          // 兼容字符串形式
          const args = innerUtil.compatibleStringParamsToObject.call(
              this,
              rest,
          );
          hybridJs.callInner.apply(this, args);
      },
  },
  {
        namespace: 'setTouchVibrationSoundEnabled',
        os: ['syber'],
        defaultParams: {
        },
        runCode(...rest) {
            // 兼容字符串形式
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
            );
            hybridJs.callInner.apply(this, args);
        },
    },
    {
      namespace: 'setVibratingEnabled',
      os: ['syber'],
      defaultParams: {
      },
      runCode(...rest) {
          // 兼容字符串形式
          const args = innerUtil.compatibleStringParamsToObject.call(
              this,
              rest,
          );
          hybridJs.callInner.apply(this, args);
      },
    },
    {
      namespace: 'stop',
      os: ['syber'],
      defaultParams: {
      },
      runCode(...rest) {
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
