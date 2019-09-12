import syber from '../src/index';
import runtimeMixin from '../src/api/native/runtime';

runtimeMixin(syber);

describe('一些API', () => {
  beforeEach(() => {
    syberh.os.syber = true;
  });
  it('clipboard', () => {
    syberh.runtime.clipboard('hello');
  });

  it('openUrl', () => {
    syberh.runtime.openUrl('http://www.baidu.com');
  });
});
