/**
 * 文件下载接口
 * @param hybrid
 */
export default function downloadMixin (hybrid) {
  const hybridJs = hybrid;
  const innerUtil = hybridJs.innerUtil;


  hybridJs.extendModule('download', [{
    namespace: 'start',
    os: ['syber'],
    defaultParams: {
      /** 下载文件地址 */
      url: '',
      /** 保存的文件名 */
      name: '',
    },
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'url',
        'name',
      );
      this.api.isLongCb = true;
      hybridJs.callInner.apply(this, args);
    },
  }, {
    namespace: 'cancel',
    os: ['syber'],
    defaultParams: {
      downloadID: ''
    },
    runCode (...rest) {
      // 兼容字符串形式
      const args = innerUtil.compatibleStringParamsToObject.call(
        this,
        rest,
        'downloadID'
      );
      hybridJs.callInner.apply(this, args);
    },
  }]);
}