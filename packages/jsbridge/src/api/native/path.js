import hybridJs from '../../hybrid';

export default function pathMixin() {

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
