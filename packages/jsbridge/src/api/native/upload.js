/**
 * 文件下载接口
 */
import hybridJs from '../../hybrid';

export default function uploadMixin () {
  const innerUtil = hybridJs.innerUtil;

  hybridJs.extendModule('upload', [{
    namespace: 'start',
    os: ['syberos'],
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'url',
        'name',
        'file'
      );
      this.api.isLongCb = true;
      hybridJs.callInner.apply(this, args);
    },
  }, {
    namespace: 'cancel',
    os: ['syberos'],
  }]);
}