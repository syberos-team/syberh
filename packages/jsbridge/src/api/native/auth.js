import hybridJs from '../../index';

export default function authMixin () {
  hybridJs.extendModule('auth', [{
    namespace: 'getToken',
    os: ['syberos'],
  }, {
    namespace: 'config',
    os: ['syberos'],
    defaultParams: {
      // 一个数组，不要传null，否则可能在iOS中会有问题
      jsApiList: [],
    },
  }]);
}