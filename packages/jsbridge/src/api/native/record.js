export default function recordMixin(hybrid) {
    const hybridJs = hybrid;
    const innerUtil = hybridJs.innerUtil;

    hybridJs.extendModule('record', [{
        namespace: 'list',
        os: ['syber'],
    }, {
        namespace: 'start',
        os: ['syber'],
    }, {
        namespace: 'pause',
        os: ['syber'],
    }, {
        namespace: 'resume',
        os: ['syber'],
    }, {
        namespace: 'stop',
        os: ['syber'],
    }, {
        namespace: 'remove',
        os: ['syber'],
        runCode(...rest) {
            const args = innerUtil.compatibleStringParamsToObject.call(
                this,
                rest,
                'path',
            );
            hybridJs.callInner.apply(this, args);
        },
    }]);
}