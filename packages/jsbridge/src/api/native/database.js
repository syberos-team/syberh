export default function databaseMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('database', [{
        namespace: 'createTable',
        os: ['syberos'],
        defaultParams: {
            sql: '',
            sqlindex: '',
        },
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'sql',
                'sqlindex',
            );
            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'selectOperate',
        os: ['syberos'],
        defaultParams: {
            sql: '',
        },
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'sql',
            );
            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'execOperate',
        os: ['syberos'],
        defaultParams: {
            sql: '',
        },
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'sql',
            );
            hybridJs.callInner.apply(this, args);
        },
    }, {
        namespace: 'isDataExists',
        os: ['syberos'],
    }, {
        namespace: 'isTableExists',
        os: ['syberos'],
        defaultParams: {
            tableName: '',
        },
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'tableName',
            );
            hybridJs.callInner.apply(this, args);
        },
    }]);
}