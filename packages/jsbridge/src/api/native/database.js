import hybridJs from '../../hybrid';

export default function databaseMixin() {
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('database', [{
        namespace: 'createTable',
        os: ['syberos'],
        defaultParams: {
            sql: '',
            sqlindex: '',
            databaseName: '',
        },
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'sql',
                'sqlindex',
                'databaseName',
            );
            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'query',
        os: ['syberos'],
        defaultParams: {
            sql: '',
            databaseName: '',
        },
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'sql',
                'databaseName',
            );
            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'execute',
        os: ['syberos'],
        defaultParams: {
            sql: '',
            databaseName: '',
        },
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'sql',
                'databaseName',
            );
            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'isDatabaseExists',
        os: ['syberos'],
    }, {
        namespace: 'isTableExists',
        os: ['syberos'],
        defaultParams: {
            tableName: '',
            databaseName: '',
        },
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'tableName',
                'databaseName',
            );
            hybridJs.callInner.apply(this, args);
        },
    }]);
}