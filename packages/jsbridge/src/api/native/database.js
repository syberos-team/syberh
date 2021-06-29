import hybridJs from '../../hybrid';

export default function databaseMixin() {
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('database', [{
        namespace: 'query',
        os: ['syberos']
    }, {
        namespace: 'exec',
        os: ['syberos']
    }, {
        namespace: 'databaseExists',
        os: ['syberos']
    }, {
        namespace: 'tableExists',
        os: ['syberos']
    }]);
}