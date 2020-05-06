/**
 * 文件下载接口
 */
import hybridJs from '../../hybrid';

export default function updateMixin () {
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('update', [{
      namespace: 'check',
      os: ['syberos'],
      runCode (...rest) {
        // 兼容字符串形式
        const args = innerUtil.compatibleStringParamsToObject.call(
          this,
          rest,
        );
        hybridJs.callInner.apply(this, args);
      }
    }, {
      namespace: 'toStore',
      os: ['syberos'],
      runCode (...rest) {
        // 兼容字符串形式
        const args = innerUtil.compatibleStringParamsToObject.call(
          this,
          rest,
        );
        hybridJs.callInner.apply(this, args);
      }
    }]);
}