import syber from '../src/index';
import runtimeMixin from '../src/api/native/runtime';

runtimeMixin(syber);

describe('一些API', () => {
    beforeEach(() => {
        syber.os.syber = true;
    });
    it('clipboard', () => {
        syber.runtime.clipboard('hello');
    });
    
    it('openUrl', () => {
        syber.runtime.openUrl('http://www.baidu.com');
    });
});
