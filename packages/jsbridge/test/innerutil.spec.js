import syber from '../src/index';
import Promise from './inner/promise';

describe('非promise情况', () => {
  beforeEach(() => {
    syberh.extendModule('test', [{
      namespace: 'fun1',
      os: ['syber'],
      defaultParams: {
        text: '',
        test2: '222',
      },
      runCode (...rest) {
        // 兼容字符串形式
        const args = syberh.innerUtil.compatibleStringParamsToObject.call(
          this,
          rest,
          'text');

        syberh.callInner.apply(this, args);
      },
    }]);
  });
  it('compatibleStringParamsToObject', () => {
    syberh.os.syber = true;
    syberh.test.fun1('hello');
  });
});

describe('promise情况', () => {
  beforeEach(() => {
    syberh.setPromise(Promise);
    syberh.extendModule('test', [{
      namespace: 'fun1',
      os: ['syber'],
      defaultParams: {
        text: '',
        test2: '222',
      },
      runCode (...rest) {
        // 兼容字符串形式
        const args = syberh.innerUtil.compatibleStringParamsToObject.call(
          this,
          rest,
          'text');

        syberh.callInner.apply(this, args);
      },
    }]);
  });
  it('compatibleStringParamsToObject', () => {
    syberh.os.syber = true;
    syberh.test.fun1('hello');
  });
});
