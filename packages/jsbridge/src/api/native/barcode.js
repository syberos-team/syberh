/**
 * 扫描条码
 * @param hybrid
 */
export default function barcodeMixin (hybrid) {
  const hybridJs = hybrid;
  const innerUtil = hybridJs.innerUtil;


  hybridJs.extendModule('barcode', [{
    namespace: 'scan',
    os: ['syberos'],
    defaultParams: {
      camera: '',
    },
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'camera',
      );
      hybridJs.callInner.apply(this, args);
    },
  }]);
}