import syber from '../src/index';
import Promise from './inner/promise';

describe('非promise情况', () => {
    beforeEach(() => {
        syber.extendModule('test', [{
            namespace: 'fun1',
            os: ['syber'],
            defaultParams: {
                text: '',
                test2: '222',
            },
            runCode(...rest) {
                // 兼容字符串形式
                const args = syber.innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'text');
                
                syber.callInner.apply(this, args);
            },
        }]);
    });
    it('compatibleStringParamsToObject', () => {
        syber.os.syber = true;
        syber.test.fun1('hello');
    });
});

describe('promise情况', () => {
    beforeEach(() => {
        syber.setPromise(Promise);
        syber.extendModule('test', [{
            namespace: 'fun1',
            os: ['syber'],
            defaultParams: {
                text: '',
                test2: '222',
            },
            runCode(...rest) {
                // 兼容字符串形式
                const args = syber.innerUtil.compatibleStringParamsToObject.call(
                    this,
                    rest,
                    'text');
                
                syber.callInner.apply(this, args);
            },
        }]);
    });
    it('compatibleStringParamsToObject', () => {
        syber.os.syber = true;
        syber.test.fun1('hello');
    });
});
