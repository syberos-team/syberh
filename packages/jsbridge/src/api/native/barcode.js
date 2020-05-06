/**
 * 扫描条码
 */
import hybridJs from '../../index';

export default function barcodeMixin () {
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