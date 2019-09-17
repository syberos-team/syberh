export default function pathMixin(hybrid) {
    const hybridJs = hybrid;

    hybridJs.extendModule('path', [
        {
            namespace: 'inner',
            os: ['syber'],
        },
        {
            namespace: 'extern',
            os: ['syber'],
        },
        {
            namespace: 'dataRoot',
            os: ['syber'],
        },
    ]);
}
