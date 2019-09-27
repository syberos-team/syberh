export default function pathMixin(hybrid) {
    const hybridJs = hybrid;

    hybridJs.extendModule('path', [
        {
            namespace: 'inner',
            os: ['syberos'],
        },
        {
            namespace: 'extern',
            os: ['syberos'],
        },
        {
            namespace: 'dataRoot',
            os: ['syberos'],
        },
    ]);
}
