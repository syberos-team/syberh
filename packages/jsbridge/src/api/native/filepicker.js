import hybridJs from '../../hybrid';

export default function filepickerMixin () {
  const innerUtil = hybridJs.innerUtil;

  hybridJs.extendModule('filepicker', [
    {
      namespace: 'open',
      os: ['syberos'],
      defaultParams: {
        title: '',
        showBack: false,
        category: '',
      },
      runCode (...rest) {
        // 兼容字符串形式
        const args = innerUtil.compatibleStringParamsToObject.call(
          this,
          rest,
          'title',
          'showBack',
          'category',
        );
        hybridJs.callInner.apply(this, args);
      },
    },
  ]);
}
